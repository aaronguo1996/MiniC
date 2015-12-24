#include <stdio.h>
#include <string.h>
#include "MEM.h"
#include "mvm_pri.h"

static void
check_gc(MVM_VirtualMachine *mvm)
{
#if 0
    mvm_garbage_collect(mvm);
#endif
    if (mvm->heap.current_heap_size > mvm->heap.current_threshold) {
        /* fprintf(stderr, "garbage collecting..."); */
        mvm_garbage_collect(mvm);
        /* fprintf(stderr, "done.\n"); */

        mvm->heap.current_threshold
            = mvm->heap.current_heap_size + HEAP_THRESHOLD_SIZE;
    }
}

static MVM_Object *
alloc_object(MVM_VirtualMachine *mvm, ObjectType type)
{
    MVM_Object *ret;

    check_gc(mvm);
    ret = MEM_malloc(sizeof(MVM_Object));
    mvm->heap.current_heap_size += sizeof(MVM_Object);
    ret->type = type;
    ret->marked = MVM_FALSE;
    ret->prev = NULL;
    ret->next = mvm->heap.header;
    mvm->heap.header = ret;
    if (ret->next) {
        ret->next->prev = ret;
    }

    return ret;
}

MVM_Object *
mvm_literal_to_mvm_string_i(MVM_VirtualMachine *mvm, MVM_Char *str)
{
    MVM_Object *ret;

    ret = alloc_object(mvm, STRING_OBJECT);
    ret->u.string.string = str;
    ret->u.string.is_literal = MVM_TRUE;

    return ret;
}

MVM_Object *
mvm_create_mvm_string_i(MVM_VirtualMachine *mvm, MVM_Char *str)
{
    MVM_Object *ret;

    ret = alloc_object(mvm, STRING_OBJECT);
    ret->u.string.string = str;
    mvm->heap.current_heap_size += sizeof(MVM_Char) * (strlen(str) + 1);
    ret->u.string.is_literal = MVM_FALSE;

    return ret;
}

MVM_Object *
alloc_array(MVM_VirtualMachine *mvm, ArrayType type, int size)
{
    MVM_Object *ret;

    ret = alloc_object(mvm, ARRAY_OBJECT);
    ret->u.array.type = type;
    ret->u.array.size = size;
    ret->u.array.alloc_size = size;

    return ret;
}

MVM_Object *
mvm_create_array_int_i(MVM_VirtualMachine *mvm, int size)
{
    MVM_Object *ret;

    ret = alloc_array(mvm, INT_ARRAY, size);
    ret->u.array.u.int_array = MEM_malloc(sizeof(int) * size);
    mvm->heap.current_heap_size += sizeof(int) * size;

    return ret;
}

MVM_Object *
MVM_create_array_int(MVM_VirtualMachine *mvm, int size)
{
    MVM_Object *ret;
    int i;

    ret = mvm_create_array_int_i(mvm, size);
    for (i = 0; i < size; i++) {
        ret->u.array.u.int_array[i] = 0;
    }

    return ret;
}

MVM_Object *
mvm_create_array_double_i(MVM_VirtualMachine *mvm, int size)
{
    MVM_Object *ret;

    ret = alloc_array(mvm, DOUBLE_ARRAY, size);
    ret->u.array.u.double_array = MEM_malloc(sizeof(double) * size);
    mvm->heap.current_heap_size += sizeof(double) * size;

    return ret;
}

MVM_Object *
MVM_create_array_double(MVM_VirtualMachine *mvm, int size)
{
    MVM_Object *ret;
    int i;

    ret = mvm_create_array_double_i(mvm, size);
    for (i = 0; i < size; i++) {
        ret->u.array.u.double_array[i] = 0.0;
    }

    return ret;
}

MVM_Object *
mvm_create_array_object_i(MVM_VirtualMachine *mvm, int size)
{
    MVM_Object *ret;

    ret = alloc_array(mvm, OBJECT_ARRAY, size);
    ret->u.array.u.object = MEM_malloc(sizeof(MVM_Object*) * size);
    mvm->heap.current_heap_size += sizeof(MVM_Object*) * size;

    return ret;
}

MVM_Object *
MVM_create_array_object(MVM_VirtualMachine *mvm, int size)
{
    MVM_Object *ret;
    int i;

    ret = mvm_create_array_object_i(mvm, size);
    for (i = 0; i < size; i++) {
        ret->u.array.u.object[i] = NULL;
    }

    return ret;
}

static void
gc_mark(MVM_Object *obj)
{
    if (obj == NULL)
        return;

    if (obj->marked)
        return;

    obj->marked = MVM_TRUE;

    if (obj->type == ARRAY_OBJECT && obj->u.array.type == OBJECT_ARRAY) {
        int i;

        for (i = 0; i < obj->u.array.size; i++) {
            gc_mark(obj->u.array.u.object[i]);
        }
    }
}

static void
gc_reset_mark(MVM_Object *obj)
{
    obj->marked = MVM_FALSE;
}

static void
gc_mark_objects(MVM_VirtualMachine *mvm)
{
    MVM_Object *obj;
    int i;

    for (obj = mvm->heap.header; obj; obj = obj->next) {
        gc_reset_mark(obj);
    }
    
    for (i = 0; i < mvm->static_v.variable_count; i++) {
        if (mvm->executable->global_variable[i].type->basic_type
            == MVM_STRING_TYPE
            || (mvm->executable->global_variable[i].type->derive != NULL
                && (mvm->executable->global_variable[i].type->derive[0].tag
                    == MVM_ARRAY_DERIVE))) {
            gc_mark(mvm->static_v.variable[i].object);
        }
    }

    for (i = 0; i < mvm->stack.stack_pointer; i++) {
        if (mvm->stack.pointer_flags[i]) {
            gc_mark(mvm->stack.stack[i].object);
        }
    }
}

static void
gc_dispose_object(MVM_VirtualMachine *mvm, MVM_Object *obj)
{
    switch (obj->type) {
    case STRING_OBJECT:
        if (!obj->u.string.is_literal) {
            mvm->heap.current_heap_size
                -= sizeof(MVM_Char) * (strlen(obj->u.string.string) + 1);
            MEM_free(obj->u.string.string);
        }
        break;
    case ARRAY_OBJECT:
        switch (obj->u.array.type) {
        case INT_ARRAY:
            mvm->heap.current_heap_size
                -= sizeof(int) * obj->u.array.alloc_size;
            MEM_free(obj->u.array.u.int_array);
            break;
        case DOUBLE_ARRAY:
            mvm->heap.current_heap_size
                -= sizeof(double) * obj->u.array.alloc_size;
            MEM_free(obj->u.array.u.double_array);
            break;
        case OBJECT_ARRAY:
            mvm->heap.current_heap_size
                -= sizeof(MVM_Object*) * obj->u.array.alloc_size;
            MEM_free(obj->u.array.u.object);
            break;
        default:
            break;
        }
        break;
    case OBJECT_TYPE_COUNT_PLUS_1:
    default:
        break;
    }
    mvm->heap.current_heap_size -= sizeof(MVM_Object);
    MEM_free(obj);
}

static void
gc_sweep_objects(MVM_VirtualMachine *mvm)
{
    MVM_Object *obj;
    MVM_Object *tmp;

    for (obj = mvm->heap.header; obj; ) {
        if (!obj->marked) {
            if (obj->prev) {
                obj->prev->next = obj->next;
            } else {
                mvm->heap.header = obj->next;
            }
            if (obj->next) {
                obj->next->prev = obj->prev;
            }
            tmp = obj->next;
            gc_dispose_object(mvm, obj);
            obj = tmp;
        } else {
            obj = obj->next;
        }
    }
}

void
mvm_garbage_collect(MVM_VirtualMachine *mvm)
{
    gc_mark_objects(mvm);
    gc_sweep_objects(mvm);
}
