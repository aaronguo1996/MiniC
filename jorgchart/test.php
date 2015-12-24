<?php
 /* User: Aaron
 * Date: 2015/11/23
 * Time: 22:13
 */

header('Content-type:text/html;charset:utf-8');
/**
 * 将数组格式array('id'=> , 'pid'=> , 'name'=> )生成树形数组格式
 * array('id'=> , 'pid'=> , 'name'=> , childrens => array() )
 */
function returnArray($result){

    $newResult = array();
    if( !empty($result) ){

        foreach ($result as $k => $v) {

            $arrTep = $v;
            $arrTep['childrens'] = array();

            //父类ID是0时，代表没有父类ID，为根节点
            if( 0 == $v['pid'] ){
                $newResult[] = $arrTep;
                continue;
            }

            if( 0 != $v['pid']){
                //添加不入数组中的子节点，可能是没有父类节点，那么将其当成根节点
                if(false === updateArray($newResult, $arrTep) ){
                    $arrTep = array('id'=> $arrTep['id'], 'pid'=>0, 'name'=>$arrTep['name'], 'childrens'=>array($arrTep));
                    $newResult[] = $arrTep;
                }

            }
        }
    }
    //测试数组是否生成树形数组
    //return $newResult;
    echo json_encode($newResult);
}

/**
 * 将当前节点插入到新的树形数组中
 * @param $newResult 树形数组地址
 * @param $arrTep 当前节点
 */
function updateArray( &$newResult, $arrTep ){

    if( !empty($newResult) ){
        foreach ($newResult as $k => $v) {
            //查询当前节点的id是否与新的树形数组的id一致，如果是，那么将当前节点存放在树形数组的childrens字段中
            if( $v['id'] == $arrTep['pid']){

                $newResult[$k]['childrens'][] = $arrTep;
                return true;

            }elseif( !empty($v['childrens']) ){
                //递归调用，查询树形数组的子节点与当前节点的关系
                if(true === updateArray( $newResult[$k]['childrens'], $arrTep )){
                    return true;
                }

            }

        }
    }
    return false;

}

//测试
$result = Array
(

1 => Array
('id' => 1,
'pid' => 0,
 	     'name' => "program"
),
2 => Array
('id' => 2,
'pid' => 1,
 	     'name' => "external_declaration_list"
),
3 => Array
('id' => 3,
'pid' => 2,
 	     'name' => "type_specifier"
),
4 => Array
('id' => 4,
'pid' => 3,
 	     'name' => "basic_type_specifier"
),
5 => Array
('id' => 5,
'pid' => 4,
 	     'name' => "integer"
),
6 => Array
('id' => 6,
'pid' => 2,
 	     'name' => "external_declaration"
),
7 => Array
('id' => 7,
'pid' => 6,
 	     'name' => "function_definition"
),
8 => Array
('id' => 8,
'pid' => 7,
 	     'name' => "statement_list"
),
9 => Array
('id' => 9,
'pid' => 8,
 	     'name' => "statement_list"
),
10 => Array
('id' => 10,
'pid' => 9,
 	     'name' => "statement_list"
),
11 => Array
('id' => 11,
'pid' => 10,
 	     'name' => "statement_list"
),
12 => Array
('id' => 12,
'pid' => 11,
 	     'name' => "statement_list"
),
13 => Array
('id' => 13,
'pid' => 12,
 	     'name' => "statement_list"
),
14 => Array
('id' => 14,
'pid' => 13,
 	     'name' => "statement_list"
),
15 => Array
('id' => 15,
'pid' => 14,
 	     'name' => "statement_list"
),
16 => Array
('id' => 16,
'pid' => 15,
 	     'name' => "statement"
),
17 => Array
('id' => 17,
'pid' => 16,
 	     'name' => "declaration_statement"
),
18 => Array
('id' => 18,
'pid' => 17,
 	     'name' => "type_specifier"
),
19 => Array
('id' => 19,
'pid' => 18,
 	     'name' => "class_type_specifier"
),
20 => Array
('id' => 20,
'pid' => 19,
 	     'name' => "m"
),
21 => Array
('id' => 21,
'pid' => 17,
 	     'name' => "rr"
),
22 => Array
('id' => 22,
'pid' => 17,
 	     'name' => ";"
),
23 => Array
('id' => 23,
'pid' => 14,
 	     'name' => "statement"
),
24 => Array
('id' => 24,
'pid' => 23,
 	     'name' => "expression"
),
25 => Array
('id' => 25,
'pid' => 24,
 	     'name' => "assignment_expression"
),
26 => Array
('id' => 26,
'pid' => 25,
 	     'name' => "primary_expression"
),
27 => Array
('id' => 27,
'pid' => 26,
 	     'name' => "primary_no_new_array"
),
28 => Array
('id' => 28,
'pid' => 27,
 	     'name' => "primary_expression"
),
29 => Array
('id' => 29,
'pid' => 28,
 	     'name' => "rr"
),
30 => Array
('id' => 30,
'pid' => 27,
 	     'name' => "."
),
31 => Array
('id' => 31,
'pid' => 27,
 	     'name' => "a"
),
32 => Array
('id' => 32,
'pid' => 25,
 	     'name' => "assignment_operator"
),
33 => Array
('id' => 33,
'pid' => 32,
 	     'name' => ":="
),
34 => Array
('id' => 34,
'pid' => 25,
 	     'name' => "assignment_expression"
),
35 => Array
('id' => 35,
'pid' => 34,
 	     'name' => "logical_or_expression"
),
36 => Array
('id' => 36,
'pid' => 35,
 	     'name' => "logical_and_expression"
),
37 => Array
('id' => 37,
'pid' => 36,
 	     'name' => "equality_expression"
),
38 => Array
('id' => 38,
'pid' => 37,
 	     'name' => "relation_expression"
),
39 => Array
('id' => 39,
'pid' => 38,
 	     'name' => "additive_expression"
),
40 => Array
('id' => 40,
'pid' => 39,
 	     'name' => "multiplicative_expression"
),
41 => Array
('id' => 41,
'pid' => 40,
 	     'name' => "unary_expression"
),
42 => Array
('id' => 42,
'pid' => 41,
 	     'name' => "postfix_expression"
),
43 => Array
('id' => 43,
'pid' => 42,
 	     'name' => "primary_expression"
),
44 => Array
('id' => 44,
'pid' => 43,
 	     'name' => "primary_no_new_expression"
),
45 => Array
('id' => 45,
'pid' => 44,
 	     'name' => "5"
),
46 => Array
('id' => 46,
'pid' => 23,
 	     'name' => ";"
),
47 => Array
('id' => 47,
'pid' => 13,
 	     'name' => "statement"
),
48 => Array
('id' => 48,
'pid' => 47,
 	     'name' => "declaration_statement"
),
49 => Array
('id' => 49,
'pid' => 48,
 	     'name' => "type_specifier"
),
50 => Array
('id' => 50,
'pid' => 49,
 	     'name' => "array_type_specifier"
),
51 => Array
('id' => 51,
'pid' => 50,
 	     'name' => "basic_type_specifier"
),
52 => Array
('id' => 52,
'pid' => 51,
 	     'name' => "integer"
),
53 => Array
('id' => 53,
'pid' => 50,
 	     'name' => "["
),
54 => Array
('id' => 54,
'pid' => 50,
 	     'name' => "]"
),
55 => Array
('id' => 55,
'pid' => 48,
 	     'name' => "a"
),
56 => Array
('id' => 56,
'pid' => 48,
 	     'name' => ";"
),
57 => Array
('id' => 57,
'pid' => 12,
 	     'name' => "statement"
),
58 => Array
('id' => 58,
'pid' => 57,
 	     'name' => "expression"
),
59 => Array
('id' => 59,
'pid' => 58,
 	     'name' => "assignment_expression"
),
60 => Array
('id' => 60,
'pid' => 59,
 	     'name' => "primary_expression"
),
61 => Array
('id' => 61,
'pid' => 60,
 	     'name' => "a"
),
62 => Array
('id' => 62,
'pid' => 59,
 	     'name' => "assignment_operator"
),
63 => Array
('id' => 63,
'pid' => 62,
 	     'name' => ":="
),
64 => Array
('id' => 64,
'pid' => 59,
 	     'name' => "assignment_expression"
),
65 => Array
('id' => 65,
'pid' => 64,
 	     'name' => "logical_or_expression"
),
66 => Array
('id' => 66,
'pid' => 65,
 	     'name' => "logical_and_expression"
),
67 => Array
('id' => 67,
'pid' => 66,
 	     'name' => "equality_expression"
),
68 => Array
('id' => 68,
'pid' => 67,
 	     'name' => "relation_expression"
),
69 => Array
('id' => 69,
'pid' => 68,
 	     'name' => "additive_expression"
),
70 => Array
('id' => 70,
'pid' => 69,
 	     'name' => "multiplicative_expression"
),
71 => Array
('id' => 71,
'pid' => 70,
 	     'name' => "unary_expression"
),
72 => Array
('id' => 72,
'pid' => 71,
 	     'name' => "postfix_expression"
),
73 => Array
('id' => 73,
'pid' => 72,
 	     'name' => "primary_expression"
),
74 => Array
('id' => 74,
'pid' => 73,
 	     'name' => "array_creation"
),
75 => Array
('id' => 75,
'pid' => 74,
 	     'name' => "new"
),
76 => Array
('id' => 76,
'pid' => 74,
 	     'name' => "basic_type_specifier"
),
77 => Array
('id' => 77,
'pid' => 76,
 	     'name' => "integer"
),
78 => Array
('id' => 78,
'pid' => 74,
 	     'name' => "dimension_expression_list"
),
79 => Array
('id' => 79,
'pid' => 78,
 	     'name' => "dimension_expression"
),
80 => Array
('id' => 80,
'pid' => 79,
 	     'name' => "["
),
81 => Array
('id' => 81,
'pid' => 79,
 	     'name' => "expression"
),
82 => Array
('id' => 82,
'pid' => 81,
 	     'name' => "assignment_expression"
),
83 => Array
('id' => 83,
'pid' => 82,
 	     'name' => "logical_or_expression"
),
84 => Array
('id' => 84,
'pid' => 83,
 	     'name' => "logical_and_expression"
),
85 => Array
('id' => 85,
'pid' => 84,
 	     'name' => "equality_expression"
),
86 => Array
('id' => 86,
'pid' => 85,
 	     'name' => "relation_expression"
),
87 => Array
('id' => 87,
'pid' => 86,
 	     'name' => "additive_expression"
),
88 => Array
('id' => 88,
'pid' => 87,
 	     'name' => "multiplicative_expression"
),
89 => Array
('id' => 89,
'pid' => 88,
 	     'name' => "unary_expression"
),
90 => Array
('id' => 90,
'pid' => 89,
 	     'name' => "postfix_expression"
),
91 => Array
('id' => 91,
'pid' => 90,
 	     'name' => "primary_expression"
),
92 => Array
('id' => 92,
'pid' => 91,
 	     'name' => "primary_no_new_expression"
),
93 => Array
('id' => 93,
'pid' => 92,
 	     'name' => "4"
),
94 => Array
('id' => 94,
'pid' => 79,
 	     'name' => "]"
),
95 => Array
('id' => 95,
'pid' => 57,
 	     'name' => ";"
),
96 => Array
('id' => 96,
'pid' => 11,
 	     'name' => "statement"
),
97 => Array
('id' => 97,
'pid' => 96,
 	     'name' => "expression"
),
98 => Array
('id' => 98,
'pid' => 97,
 	     'name' => "assignment_expression"
),
99 => Array
('id' => 99,
'pid' => 98,
 	     'name' => "primary_expression"
),
100 => Array
('id' => 100,
'pid' => 99,
 	     'name' => "a"
),
101 => Array
('id' => 101,
'pid' => 98,
 	     'name' => "assignment_operator"
),
102 => Array
('id' => 102,
'pid' => 101,
 	     'name' => ":="
),
103 => Array
('id' => 103,
'pid' => 98,
 	     'name' => "assignment_expression"
),
104 => Array
('id' => 104,
'pid' => 103,
 	     'name' => "logical_or_expression"
),
105 => Array
('id' => 105,
'pid' => 104,
 	     'name' => "logical_and_expression"
),
106 => Array
('id' => 106,
'pid' => 105,
 	     'name' => "equality_expression"
),
107 => Array
('id' => 107,
'pid' => 106,
 	     'name' => "relation_expression"
),
108 => Array
('id' => 108,
'pid' => 107,
 	     'name' => "additive_expression"
),
109 => Array
('id' => 109,
'pid' => 108,
 	     'name' => "multiplicative_expression"
),
110 => Array
('id' => 110,
'pid' => 109,
 	     'name' => "unary_expression"
),
111 => Array
('id' => 111,
'pid' => 110,
 	     'name' => "postfix_expression"
),
112 => Array
('id' => 112,
'pid' => 111,
 	     'name' => "primary_expression"
),
113 => Array
('id' => 113,
'pid' => 112,
 	     'name' => "primary_no_new_expression"
),
114 => Array
('id' => 114,
'pid' => 113,
 	     'name' => "array_literal"
),
115 => Array
('id' => 115,
'pid' => 114,
 	     'name' => "{"
),
116 => Array
('id' => 116,
'pid' => 114,
 	     'name' => "expression_list"
),
117 => Array
('id' => 117,
'pid' => 116,
 	     'name' => "expression_list"
),
118 => Array
('id' => 118,
'pid' => 117,
 	     'name' => "expression_list"
),
119 => Array
('id' => 119,
'pid' => 118,
 	     'name' => "expression_list"
),
120 => Array
('id' => 120,
'pid' => 119,
 	     'name' => "assignment_expression"
),
121 => Array
('id' => 121,
'pid' => 120,
 	     'name' => "logical_or_expression"
),
122 => Array
('id' => 122,
'pid' => 121,
 	     'name' => "logical_and_expression"
),
123 => Array
('id' => 123,
'pid' => 122,
 	     'name' => "equality_expression"
),
124 => Array
('id' => 124,
'pid' => 123,
 	     'name' => "relation_expression"
),
125 => Array
('id' => 125,
'pid' => 124,
 	     'name' => "additive_expression"
),
126 => Array
('id' => 126,
'pid' => 125,
 	     'name' => "multiplicative_expression"
),
127 => Array
('id' => 127,
'pid' => 126,
 	     'name' => "unary_expression"
),
128 => Array
('id' => 128,
'pid' => 127,
 	     'name' => "postfix_expression"
),
129 => Array
('id' => 129,
'pid' => 128,
 	     'name' => "primary_expression"
),
130 => Array
('id' => 130,
'pid' => 129,
 	     'name' => "primary_no_new_expression"
),
131 => Array
('id' => 131,
'pid' => 130,
 	     'name' => "1"
),
132 => Array
('id' => 132,
'pid' => 118,
 	     'name' => ","
),
133 => Array
('id' => 133,
'pid' => 118,
 	     'name' => "assignment_expression"
),
134 => Array
('id' => 134,
'pid' => 133,
 	     'name' => "logical_or_expression"
),
135 => Array
('id' => 135,
'pid' => 134,
 	     'name' => "logical_and_expression"
),
136 => Array
('id' => 136,
'pid' => 135,
 	     'name' => "equality_expression"
),
137 => Array
('id' => 137,
'pid' => 136,
 	     'name' => "relation_expression"
),
138 => Array
('id' => 138,
'pid' => 137,
 	     'name' => "additive_expression"
),
139 => Array
('id' => 139,
'pid' => 138,
 	     'name' => "multiplicative_expression"
),
140 => Array
('id' => 140,
'pid' => 139,
 	     'name' => "unary_expression"
),
141 => Array
('id' => 141,
'pid' => 140,
 	     'name' => "postfix_expression"
),
142 => Array
('id' => 142,
'pid' => 141,
 	     'name' => "primary_expression"
),
143 => Array
('id' => 143,
'pid' => 142,
 	     'name' => "primary_no_new_expression"
),
144 => Array
('id' => 144,
'pid' => 143,
 	     'name' => "2"
),
145 => Array
('id' => 145,
'pid' => 117,
 	     'name' => ","
),
146 => Array
('id' => 146,
'pid' => 117,
 	     'name' => "assignment_expression"
),
147 => Array
('id' => 147,
'pid' => 146,
 	     'name' => "logical_or_expression"
),
148 => Array
('id' => 148,
'pid' => 147,
 	     'name' => "logical_and_expression"
),
149 => Array
('id' => 149,
'pid' => 148,
 	     'name' => "equality_expression"
),
150 => Array
('id' => 150,
'pid' => 149,
 	     'name' => "relation_expression"
),
151 => Array
('id' => 151,
'pid' => 150,
 	     'name' => "additive_expression"
),
152 => Array
('id' => 152,
'pid' => 151,
 	     'name' => "multiplicative_expression"
),
153 => Array
('id' => 153,
'pid' => 152,
 	     'name' => "unary_expression"
),
154 => Array
('id' => 154,
'pid' => 153,
 	     'name' => "postfix_expression"
),
155 => Array
('id' => 155,
'pid' => 154,
 	     'name' => "primary_expression"
),
156 => Array
('id' => 156,
'pid' => 155,
 	     'name' => "primary_no_new_expression"
),
157 => Array
('id' => 157,
'pid' => 156,
 	     'name' => "3"
),
158 => Array
('id' => 158,
'pid' => 116,
 	     'name' => ","
),
159 => Array
('id' => 159,
'pid' => 116,
 	     'name' => "assignment_expression"
),
160 => Array
('id' => 160,
'pid' => 159,
 	     'name' => "logical_or_expression"
),
161 => Array
('id' => 161,
'pid' => 160,
 	     'name' => "logical_and_expression"
),
162 => Array
('id' => 162,
'pid' => 161,
 	     'name' => "equality_expression"
),
163 => Array
('id' => 163,
'pid' => 162,
 	     'name' => "relation_expression"
),
164 => Array
('id' => 164,
'pid' => 163,
 	     'name' => "additive_expression"
),
165 => Array
('id' => 165,
'pid' => 164,
 	     'name' => "multiplicative_expression"
),
166 => Array
('id' => 166,
'pid' => 165,
 	     'name' => "unary_expression"
),
167 => Array
('id' => 167,
'pid' => 166,
 	     'name' => "postfix_expression"
),
168 => Array
('id' => 168,
'pid' => 167,
 	     'name' => "primary_expression"
),
169 => Array
('id' => 169,
'pid' => 168,
 	     'name' => "primary_no_new_expression"
),
170 => Array
('id' => 170,
'pid' => 169,
 	     'name' => "4"
),
171 => Array
('id' => 171,
'pid' => 114,
 	     'name' => "}"
),
172 => Array
('id' => 172,
'pid' => 96,
 	     'name' => ";"
),
173 => Array
('id' => 173,
'pid' => 10,
 	     'name' => "statement"
),
174 => Array
('id' => 174,
'pid' => 173,
 	     'name' => "declaraton_statement"
),
175 => Array
('id' => 175,
'pid' => 174,
 	     'name' => "type_specifier"
),
176 => Array
('id' => 176,
'pid' => 175,
 	     'name' => "basic_type_specifier"
),
177 => Array
('id' => 177,
'pid' => 176,
 	     'name' => "integer"
),
178 => Array
('id' => 178,
'pid' => 174,
 	     'name' => "b"
),
179 => Array
('id' => 179,
'pid' => 174,
 	     'name' => ":="
),
180 => Array
('id' => 180,
'pid' => 174,
 	     'name' => "expression"
),
181 => Array
('id' => 181,
'pid' => 180,
 	     'name' => "assignment_expression"
),
182 => Array
('id' => 182,
'pid' => 181,
 	     'name' => "logical_or_expression"
),
183 => Array
('id' => 183,
'pid' => 182,
 	     'name' => "logical_and_expression"
),
184 => Array
('id' => 184,
'pid' => 183,
 	     'name' => "equality_expression"
),
185 => Array
('id' => 185,
'pid' => 184,
 	     'name' => "relation_expression"
),
186 => Array
('id' => 186,
'pid' => 185,
 	     'name' => "additive_expression"
),
187 => Array
('id' => 187,
'pid' => 186,
 	     'name' => "multiplicative_expression"
),
188 => Array
('id' => 188,
'pid' => 187,
 	     'name' => "unary_expression"
),
189 => Array
('id' => 189,
'pid' => 188,
 	     'name' => "postfix_expression"
),
190 => Array
('id' => 190,
'pid' => 189,
 	     'name' => "primary_expression"
),
191 => Array
('id' => 191,
'pid' => 190,
 	     'name' => "primary_no_new_expression"
),
192 => Array
('id' => 192,
'pid' => 191,
 	     'name' => "3"
),
193 => Array
('id' => 193,
'pid' => 174,
 	     'name' => ";"
),
194 => Array
('id' => 194,
'pid' => 9,
 	     'name' => "statement"
),
195 => Array
('id' => 195,
'pid' => 194,
 	     'name' => "if_statement"
),
196 => Array
('id' => 196,
'pid' => 195,
 	     'name' => "IF"
),
197 => Array
('id' => 197,
'pid' => 195,
 	     'name' => "("
),
198 => Array
('id' => 198,
'pid' => 195,
 	     'name' => "expression"
),
199 => Array
('id' => 199,
'pid' => 198,
 	     'name' => "assignment_expression"
),
200 => Array
('id' => 200,
'pid' => 199,
 	     'name' => "logical_or_expression"
),
201 => Array
('id' => 201,
'pid' => 200,
 	     'name' => "logical_and_expression"
),
202 => Array
('id' => 202,
'pid' => 201,
 	     'name' => "equality_expression"
),
203 => Array
('id' => 203,
'pid' => 202,
 	     'name' => "relation_expression"
),
204 => Array
('id' => 204,
'pid' => 203,
 	     'name' => "relation_expression"
),
205 => Array
('id' => 205,
'pid' => 204,
 	     'name' => "additive_expression"
),
206 => Array
('id' => 206,
'pid' => 205,
 	     'name' => "multiplicative_expression"
),
207 => Array
('id' => 207,
'pid' => 206,
 	     'name' => "unary_expression"
),
208 => Array
('id' => 208,
'pid' => 207,
 	     'name' => "postfix_expression"
),
209 => Array
('id' => 209,
'pid' => 208,
 	     'name' => "primary_expression"
),
210 => Array
('id' => 210,
'pid' => 209,
 	     'name' => "b"
),
211 => Array
('id' => 211,
'pid' => 203,
 	     'name' => ">="
),
212 => Array
('id' => 212,
'pid' => 203,
 	     'name' => "additive_expression"
),
213 => Array
('id' => 213,
'pid' => 212,
 	     'name' => "multiplicative_expression"
),
214 => Array
('id' => 214,
'pid' => 213,
 	     'name' => "unary_expression"
),
215 => Array
('id' => 215,
'pid' => 214,
 	     'name' => "postfix_expression"
),
216 => Array
('id' => 216,
'pid' => 215,
 	     'name' => "primary_expression"
),
217 => Array
('id' => 217,
'pid' => 216,
 	     'name' => "primary_no_new_expression"
),
218 => Array
('id' => 218,
'pid' => 217,
 	     'name' => "10"
),
219 => Array
('id' => 219,
'pid' => 195,
 	     'name' => ")"
),
220 => Array
('id' => 220,
'pid' => 195,
 	     'name' => "block"
),
221 => Array
('id' => 221,
'pid' => 220,
 	     'name' => "{"
),
222 => Array
('id' => 222,
'pid' => 220,
 	     'name' => "statement_list"
),
223 => Array
('id' => 223,
'pid' => 222,
 	     'name' => "statement"
),
224 => Array
('id' => 224,
'pid' => 223,
 	     'name' => "declaraton_statement"
),
225 => Array
('id' => 225,
'pid' => 224,
 	     'name' => "type_specifier"
),
226 => Array
('id' => 226,
'pid' => 225,
 	     'name' => "basic_type_specifier"
),
227 => Array
('id' => 227,
'pid' => 226,
 	     'name' => "integer"
),
228 => Array
('id' => 228,
'pid' => 224,
 	     'name' => "c"
),
229 => Array
('id' => 229,
'pid' => 224,
 	     'name' => ":="
),
230 => Array
('id' => 230,
'pid' => 224,
 	     'name' => "expression"
),
231 => Array
('id' => 231,
'pid' => 230,
 	     'name' => "assignment_expression"
),
232 => Array
('id' => 232,
'pid' => 231,
 	     'name' => "logical_or_expression"
),
233 => Array
('id' => 233,
'pid' => 232,
 	     'name' => "logical_and_expression"
),
234 => Array
('id' => 234,
'pid' => 233,
 	     'name' => "equality_expression"
),
235 => Array
('id' => 235,
'pid' => 234,
 	     'name' => "relation_expression"
),
236 => Array
('id' => 236,
'pid' => 235,
 	     'name' => "additive_expression"
),
237 => Array
('id' => 237,
'pid' => 236,
 	     'name' => "multiplicative_expression"
),
238 => Array
('id' => 238,
'pid' => 237,
 	     'name' => "unary_expression"
),
239 => Array
('id' => 239,
'pid' => 238,
 	     'name' => "postfix_expression"
),
240 => Array
('id' => 240,
'pid' => 239,
 	     'name' => "primary_expression"
),
241 => Array
('id' => 241,
'pid' => 240,
 	     'name' => "primary_no_new_expression"
),
242 => Array
('id' => 242,
'pid' => 241,
 	     'name' => "0"
),
243 => Array
('id' => 243,
'pid' => 224,
 	     'name' => ";"
),
244 => Array
('id' => 244,
'pid' => 220,
 	     'name' => "}"
),
245 => Array
('id' => 245,
'pid' => 195,
 	     'name' => "elseif_list"
),
246 => Array
('id' => 246,
'pid' => 245,
 	     'name' => "elseif"
),
247 => Array
('id' => 247,
'pid' => 246,
 	     'name' => "ELSEIF"
),
248 => Array
('id' => 248,
'pid' => 246,
 	     'name' => "("
),
249 => Array
('id' => 249,
'pid' => 246,
 	     'name' => "expression"
),
250 => Array
('id' => 250,
'pid' => 249,
 	     'name' => "assignment_expression"
),
251 => Array
('id' => 251,
'pid' => 250,
 	     'name' => "logical_or_expression"
),
252 => Array
('id' => 252,
'pid' => 251,
 	     'name' => "logical_and_expression"
),
253 => Array
('id' => 253,
'pid' => 246,
 	     'name' => ")"
),
254 => Array
('id' => 254,
'pid' => 246,
 	     'name' => "block"
),
255 => Array
('id' => 255,
'pid' => 254,
 	     'name' => "{"
),
256 => Array
('id' => 256,
'pid' => 254,
 	     'name' => "statement_list"
),
257 => Array
('id' => 257,
'pid' => 256,
 	     'name' => "statement"
),
258 => Array
('id' => 258,
'pid' => 257,
 	     'name' => "declaraton_statement"
),
259 => Array
('id' => 259,
'pid' => 258,
 	     'name' => "type_specifier"
),
260 => Array
('id' => 260,
'pid' => 259,
 	     'name' => "basic_type_specifier"
),
261 => Array
('id' => 261,
'pid' => 260,
 	     'name' => "integer"
),
262 => Array
('id' => 262,
'pid' => 258,
 	     'name' => "c"
),
263 => Array
('id' => 263,
'pid' => 258,
 	     'name' => ":="
),
264 => Array
('id' => 264,
'pid' => 258,
 	     'name' => "expression"
),
265 => Array
('id' => 265,
'pid' => 264,
 	     'name' => "assignment_expression"
),
266 => Array
('id' => 266,
'pid' => 265,
 	     'name' => "logical_or_expression"
),
267 => Array
('id' => 267,
'pid' => 266,
 	     'name' => "logical_and_expression"
),
268 => Array
('id' => 268,
'pid' => 267,
 	     'name' => "equality_expression"
),
269 => Array
('id' => 269,
'pid' => 268,
 	     'name' => "relation_expression"
),
270 => Array
('id' => 270,
'pid' => 269,
 	     'name' => "additive_expression"
),
271 => Array
('id' => 271,
'pid' => 270,
 	     'name' => "multiplicative_expression"
),
272 => Array
('id' => 272,
'pid' => 271,
 	     'name' => "unary_expression"
),
273 => Array
('id' => 273,
'pid' => 272,
 	     'name' => "postfix_expression"
),
274 => Array
('id' => 274,
'pid' => 273,
 	     'name' => "primary_expression"
),
275 => Array
('id' => 275,
'pid' => 274,
 	     'name' => "primary_no_new_expression"
),
276 => Array
('id' => 276,
'pid' => 275,
 	     'name' => "9"
),
277 => Array
('id' => 277,
'pid' => 258,
 	     'name' => ";"
),
278 => Array
('id' => 278,
'pid' => 254,
 	     'name' => "}"
),
279 => Array
('id' => 279,
'pid' => 195,
 	     'name' => "ELSE"
),
280 => Array
('id' => 280,
'pid' => 195,
 	     'name' => "block"
),
281 => Array
('id' => 281,
'pid' => 280,
 	     'name' => "{"
),
282 => Array
('id' => 282,
'pid' => 280,
 	     'name' => "statement_list"
),
283 => Array
('id' => 283,
'pid' => 282,
 	     'name' => "statement"
),
284 => Array
('id' => 284,
'pid' => 283,
 	     'name' => "declaraton_statement"
),
285 => Array
('id' => 285,
'pid' => 284,
 	     'name' => "type_specifier"
),
286 => Array
('id' => 286,
'pid' => 285,
 	     'name' => "basic_type_specifier"
),
287 => Array
('id' => 287,
'pid' => 286,
 	     'name' => "integer"
),
288 => Array
('id' => 288,
'pid' => 284,
 	     'name' => "d"
),
289 => Array
('id' => 289,
'pid' => 284,
 	     'name' => ":="
),
290 => Array
('id' => 290,
'pid' => 284,
 	     'name' => "expression"
),
291 => Array
('id' => 291,
'pid' => 290,
 	     'name' => "assignment_expression"
),
292 => Array
('id' => 292,
'pid' => 291,
 	     'name' => "logical_or_expression"
),
293 => Array
('id' => 293,
'pid' => 292,
 	     'name' => "logical_and_expression"
),
294 => Array
('id' => 294,
'pid' => 293,
 	     'name' => "equality_expression"
),
295 => Array
('id' => 295,
'pid' => 294,
 	     'name' => "relation_expression"
),
296 => Array
('id' => 296,
'pid' => 295,
 	     'name' => "additive_expression"
),
297 => Array
('id' => 297,
'pid' => 296,
 	     'name' => "multiplicative_expression"
),
298 => Array
('id' => 298,
'pid' => 297,
 	     'name' => "unary_expression"
),
299 => Array
('id' => 299,
'pid' => 298,
 	     'name' => "postfix_expression"
),
300 => Array
('id' => 300,
'pid' => 299,
 	     'name' => "primary_expression"
),
301 => Array
('id' => 301,
'pid' => 300,
 	     'name' => "primary_no_new_expression"
),
302 => Array
('id' => 302,
'pid' => 301,
 	     'name' => "12"
),
303 => Array
('id' => 303,
'pid' => 284,
 	     'name' => ";"
),
304 => Array
('id' => 304,
'pid' => 280,
 	     'name' => "}"
),
305 => Array
('id' => 305,
'pid' => 8,
 	     'name' => "statement"
),
306 => Array
('id' => 306,
'pid' => 305,
 	     'name' => "declaration_statement"
),
307 => Array
('id' => 307,
'pid' => 306,
 	     'name' => "type_specifier"
),
308 => Array
('id' => 308,
'pid' => 307,
 	     'name' => "basic_type_specifier"
),
309 => Array
('id' => 309,
'pid' => 308,
 	     'name' => "integer"
),
310 => Array
('id' => 310,
'pid' => 306,
 	     'name' => "i"
),
311 => Array
('id' => 311,
'pid' => 306,
 	     'name' => ";"
),
312 => Array
('id' => 312,
'pid' => 7,
 	     'name' => "test"
),
313 => Array
('id' => 313,
'pid' => 7,
 	     'name' => "("
),
314 => Array
('id' => 314,
'pid' => 7,
 	     'name' => ")"
),
315 => Array
('id' => 315,
'pid' => 7,
 	     'name' => "block"
),
316 => Array
('id' => 316,
'pid' => 315,
 	     'name' => "{"
),
317 => Array
('id' => 317,
'pid' => 315,
 	     'name' => "statement_list"
),
318 => Array
('id' => 318,
'pid' => 317,
 	     'name' => "statement_list"
),
319 => Array
('id' => 319,
'pid' => 318,
 	     'name' => "statement_list"
),
320 => Array
('id' => 320,
'pid' => 319,
 	     'name' => "statement_list"
),
321 => Array
('id' => 321,
'pid' => 320,
 	     'name' => "label_opt"
),
322 => Array
('id' => 322,
'pid' => 321,
 	     'name' => "#"
),
323 => Array
('id' => 323,
'pid' => 320,
 	     'name' => "statement"
),
324 => Array
('id' => 324,
'pid' => 323,
 	     'name' => "for_statement"
),
325 => Array
('id' => 325,
'pid' => 324,
 	     'name' => "expression_opt"
),
326 => Array
('id' => 326,
'pid' => 325,
 	     'name' => "expression"
),
327 => Array
('id' => 327,
'pid' => 326,
 	     'name' => "assignment_expression"
),
328 => Array
('id' => 328,
'pid' => 327,
 	     'name' => "logical_or_expression"
),
329 => Array
('id' => 329,
'pid' => 328,
 	     'name' => "logical_and_expression"
),
330 => Array
('id' => 330,
'pid' => 329,
 	     'name' => "equlity_expression"
),
331 => Array
('id' => 331,
'pid' => 330,
 	     'name' => "equality_expression"
),
332 => Array
('id' => 332,
'pid' => 331,
 	     'name' => "relation_expression"
),
333 => Array
('id' => 333,
'pid' => 332,
 	     'name' => "additive_expression"
),
334 => Array
('id' => 334,
'pid' => 333,
 	     'name' => "multiplicative_expression"
),
335 => Array
('id' => 335,
'pid' => 334,
 	     'name' => "unary_expression"
),
336 => Array
('id' => 336,
'pid' => 335,
 	     'name' => "postfix_expression"
),
337 => Array
('id' => 337,
'pid' => 336,
 	     'name' => "primary_expression"
),
338 => Array
('id' => 338,
'pid' => 337,
 	     'name' => "i"
),
339 => Array
('id' => 339,
'pid' => 330,
 	     'name' => "="
),
340 => Array
('id' => 340,
'pid' => 330,
 	     'name' => "relation_expression"
),
341 => Array
('id' => 341,
'pid' => 340,
 	     'name' => "additive_expression"
),
342 => Array
('id' => 342,
'pid' => 341,
 	     'name' => "multiplicative_expression"
),
343 => Array
('id' => 343,
'pid' => 342,
 	     'name' => "unary_expression"
),
344 => Array
('id' => 344,
'pid' => 343,
 	     'name' => "postfix_expression"
),
345 => Array
('id' => 345,
'pid' => 344,
 	     'name' => "primary_expression"
),
346 => Array
('id' => 346,
'pid' => 345,
 	     'name' => "primary_no_new_expression"
),
347 => Array
('id' => 347,
'pid' => 346,
 	     'name' => "0"
),
348 => Array
('id' => 348,
'pid' => 324,
 	     'name' => "for"
),
349 => Array
('id' => 349,
'pid' => 324,
 	     'name' => "("
),
350 => Array
('id' => 350,
'pid' => 324,
 	     'name' => ""
),
351 => Array
('id' => 351,
'pid' => 324,
 	     'name' => ";"
),
352 => Array
('id' => 352,
'pid' => 324,
 	     'name' => "expression_opt"
),
353 => Array
('id' => 353,
'pid' => 352,
 	     'name' => "expression"
),
354 => Array
('id' => 354,
'pid' => 353,
 	     'name' => "assignment_expression"
),
355 => Array
('id' => 355,
'pid' => 354,
 	     'name' => "logical_or_expression"
),
356 => Array
('id' => 356,
'pid' => 355,
 	     'name' => "logical_and_expression"
),
357 => Array
('id' => 357,
'pid' => 356,
 	     'name' => "equality_expression"
),
358 => Array
('id' => 358,
'pid' => 357,
 	     'name' => "relation_expression"
),
359 => Array
('id' => 359,
'pid' => 358,
 	     'name' => "relation_expression"
),
360 => Array
('id' => 360,
'pid' => 359,
 	     'name' => "additive_expression"
),
361 => Array
('id' => 361,
'pid' => 360,
 	     'name' => "multiplicative_expression"
),
362 => Array
('id' => 362,
'pid' => 361,
 	     'name' => "unary_expression"
),
363 => Array
('id' => 363,
'pid' => 362,
 	     'name' => "postfix_expression"
),
364 => Array
('id' => 364,
'pid' => 363,
 	     'name' => "primary_expression"
),
365 => Array
('id' => 365,
'pid' => 364,
 	     'name' => "i"
),
366 => Array
('id' => 366,
'pid' => 358,
 	     'name' => "<"
),
367 => Array
('id' => 367,
'pid' => 358,
 	     'name' => "additive_expression"
),
368 => Array
('id' => 368,
'pid' => 367,
 	     'name' => "multiplicative_expression"
),
369 => Array
('id' => 369,
'pid' => 368,
 	     'name' => "unary_expression"
),
370 => Array
('id' => 370,
'pid' => 369,
 	     'name' => "postfix_expression"
),
371 => Array
('id' => 371,
'pid' => 370,
 	     'name' => "primary_expression"
),
372 => Array
('id' => 372,
'pid' => 371,
 	     'name' => "primary_no_new_expression"
),
373 => Array
('id' => 373,
'pid' => 372,
 	     'name' => "9"
),
374 => Array
('id' => 374,
'pid' => 324,
 	     'name' => ";"
),
375 => Array
('id' => 375,
'pid' => 324,
 	     'name' => "expression_opt"
),
376 => Array
('id' => 376,
'pid' => 375,
 	     'name' => "expression"
),
377 => Array
('id' => 377,
'pid' => 376,
 	     'name' => "assignment_expression"
),
378 => Array
('id' => 378,
'pid' => 377,
 	     'name' => "logical_or_expression"
),
379 => Array
('id' => 379,
'pid' => 378,
 	     'name' => "logical_and_expression"
),
380 => Array
('id' => 380,
'pid' => 379,
 	     'name' => "equality_expression"
),
381 => Array
('id' => 381,
'pid' => 380,
 	     'name' => "relation_expression"
),
382 => Array
('id' => 382,
'pid' => 381,
 	     'name' => "additive_expression"
),
383 => Array
('id' => 383,
'pid' => 382,
 	     'name' => "multiplicative_expression"
),
384 => Array
('id' => 384,
'pid' => 383,
 	     'name' => "unary_expression"
),
385 => Array
('id' => 385,
'pid' => 384,
 	     'name' => "postfix_expression"
),
386 => Array
('id' => 386,
'pid' => 385,
 	     'name' => "primary_expression"
),
387 => Array
('id' => 387,
'pid' => 386,
 	     'name' => "i"
),
388 => Array
('id' => 388,
'pid' => 385,
 	     'name' => "++"
),
389 => Array
('id' => 389,
'pid' => 324,
 	     'name' => ")"
),
390 => Array
('id' => 390,
'pid' => 324,
 	     'name' => "block"
),
391 => Array
('id' => 391,
'pid' => 390,
 	     'name' => "{"
),
392 => Array
('id' => 392,
'pid' => 390,
 	     'name' => "statement_list"
),
393 => Array
('id' => 393,
'pid' => 392,
 	     'name' => "statement"
),
394 => Array
('id' => 394,
'pid' => 393,
 	     'name' => "expression"
),
395 => Array
('id' => 395,
'pid' => 394,
 	     'name' => "assignment_expression"
),
396 => Array
('id' => 396,
'pid' => 395,
 	     'name' => "logical_or_expression"
),
397 => Array
('id' => 397,
'pid' => 396,
 	     'name' => "logical_and_expression"
),
398 => Array
('id' => 398,
'pid' => 397,
 	     'name' => "equality_expression"
),
399 => Array
('id' => 399,
'pid' => 398,
 	     'name' => "relation_expression"
),
400 => Array
('id' => 400,
'pid' => 399,
 	     'name' => "additive_expression"
),
401 => Array
('id' => 401,
'pid' => 400,
 	     'name' => "multiplicative_expression"
),
402 => Array
('id' => 402,
'pid' => 401,
 	     'name' => "unary_expression"
),
403 => Array
('id' => 403,
'pid' => 402,
 	     'name' => "postfix_expression"
),
404 => Array
('id' => 404,
'pid' => 403,
 	     'name' => "primary_expression"
),
405 => Array
('id' => 405,
'pid' => 404,
 	     'name' => "b"
),
406 => Array
('id' => 406,
'pid' => 403,
 	     'name' => "--"
),
407 => Array
('id' => 407,
'pid' => 393,
 	     'name' => ";"
),
408 => Array
('id' => 408,
'pid' => 390,
 	     'name' => "}"
),
409 => Array
('id' => 409,
'pid' => 319,
 	     'name' => "statement"
),
410 => Array
('id' => 410,
'pid' => 409,
 	     'name' => "while_statement"
),
411 => Array
('id' => 411,
'pid' => 410,
 	     'name' => "label_opt"
),
412 => Array
('id' => 412,
'pid' => 411,
 	     'name' => "#"
),
413 => Array
('id' => 413,
'pid' => 410,
 	     'name' => "while"
),
414 => Array
('id' => 414,
'pid' => 410,
 	     'name' => "("
),
415 => Array
('id' => 415,
'pid' => 410,
 	     'name' => "expression"
),
416 => Array
('id' => 416,
'pid' => 415,
 	     'name' => "assignment_expression"
),
417 => Array
('id' => 417,
'pid' => 416,
 	     'name' => "logical_or_expression"
),
418 => Array
('id' => 418,
'pid' => 417,
 	     'name' => "logical_and_expression"
),
419 => Array
('id' => 419,
'pid' => 418,
 	     'name' => "equality_expression"
),
420 => Array
('id' => 420,
'pid' => 419,
 	     'name' => "relation_expression"
),
421 => Array
('id' => 421,
'pid' => 420,
 	     'name' => "relation_expression"
),
422 => Array
('id' => 422,
'pid' => 421,
 	     'name' => "additive_expression"
),
423 => Array
('id' => 423,
'pid' => 422,
 	     'name' => "multiplicative_expression"
),
424 => Array
('id' => 424,
'pid' => 423,
 	     'name' => "unary_expression"
),
425 => Array
('id' => 425,
'pid' => 424,
 	     'name' => "postfix_expression"
),
426 => Array
('id' => 426,
'pid' => 425,
 	     'name' => "primary_expression"
),
427 => Array
('id' => 427,
'pid' => 426,
 	     'name' => "b"
),
428 => Array
('id' => 428,
'pid' => 420,
 	     'name' => "<"
),
429 => Array
('id' => 429,
'pid' => 420,
 	     'name' => "additive_expression"
),
430 => Array
('id' => 430,
'pid' => 429,
 	     'name' => "multiplicative_expression"
),
431 => Array
('id' => 431,
'pid' => 430,
 	     'name' => "unary_expression"
),
432 => Array
('id' => 432,
'pid' => 431,
 	     'name' => "postfix_expression"
),
433 => Array
('id' => 433,
'pid' => 432,
 	     'name' => "primary_expression"
),
434 => Array
('id' => 434,
'pid' => 433,
 	     'name' => "primary_no_new_expression"
),
435 => Array
('id' => 435,
'pid' => 434,
 	     'name' => "0"
),
436 => Array
('id' => 436,
'pid' => 410,
 	     'name' => ")"
),
437 => Array
('id' => 437,
'pid' => 410,
 	     'name' => "block"
),
438 => Array
('id' => 438,
'pid' => 437,
 	     'name' => "{"
),
439 => Array
('id' => 439,
'pid' => 437,
 	     'name' => "statement_list"
),
440 => Array
('id' => 440,
'pid' => 439,
 	     'name' => "statement"
),
441 => Array
('id' => 441,
'pid' => 440,
 	     'name' => "expression"
),
442 => Array
('id' => 442,
'pid' => 441,
 	     'name' => "assignment_expression"
),
443 => Array
('id' => 443,
'pid' => 442,
 	     'name' => "logical_or_expression"
),
444 => Array
('id' => 444,
'pid' => 443,
 	     'name' => "logical_and_expression"
),
445 => Array
('id' => 445,
'pid' => 444,
 	     'name' => "equality_expression"
),
446 => Array
('id' => 446,
'pid' => 445,
 	     'name' => "relation_expression"
),
447 => Array
('id' => 447,
'pid' => 446,
 	     'name' => "additive_expression"
),
448 => Array
('id' => 448,
'pid' => 447,
 	     'name' => "multiplicative_expression"
),
449 => Array
('id' => 449,
'pid' => 448,
 	     'name' => "unary_expression"
),
450 => Array
('id' => 450,
'pid' => 449,
 	     'name' => "postfix_expression"
),
451 => Array
('id' => 451,
'pid' => 450,
 	     'name' => "primary_expression"
),
452 => Array
('id' => 452,
'pid' => 451,
 	     'name' => "b"
),
453 => Array
('id' => 453,
'pid' => 450,
 	     'name' => "++"
),
454 => Array
('id' => 454,
'pid' => 440,
 	     'name' => ";"
),
455 => Array
('id' => 455,
'pid' => 437,
 	     'name' => "}"
),
456 => Array
('id' => 456,
'pid' => 318,
 	     'name' => "statement"
),
457 => Array
('id' => 457,
'pid' => 456,
 	     'name' => "while_statement"
),
458 => Array
('id' => 458,
'pid' => 457,
 	     'name' => "label_opt"
),
459 => Array
('id' => 459,
'pid' => 458,
 	     'name' => "#"
),
460 => Array
('id' => 460,
'pid' => 457,
 	     'name' => "foreach"
),
461 => Array
('id' => 461,
'pid' => 457,
 	     'name' => "("
),
462 => Array
('id' => 462,
'pid' => 457,
 	     'name' => "a"
),
463 => Array
('id' => 463,
'pid' => 457,
 	     'name' => ":"
),
464 => Array
('id' => 464,
'pid' => 457,
 	     'name' => "expression"
),
465 => Array
('id' => 465,
'pid' => 464,
 	     'name' => "assignment_expression"
),
466 => Array
('id' => 466,
'pid' => 465,
 	     'name' => "logical_or_expression"
),
467 => Array
('id' => 467,
'pid' => 466,
 	     'name' => "logical_and_expression"
),
468 => Array
('id' => 468,
'pid' => 467,
 	     'name' => "equality_expression"
),
469 => Array
('id' => 469,
'pid' => 468,
 	     'name' => "relation_expression"
),
470 => Array
('id' => 470,
'pid' => 469,
 	     'name' => "additive_expression"
),
471 => Array
('id' => 471,
'pid' => 470,
 	     'name' => "multiplicative_expression"
),
472 => Array
('id' => 472,
'pid' => 471,
 	     'name' => "unary_expression"
),
473 => Array
('id' => 473,
'pid' => 472,
 	     'name' => "postfix_expression"
),
474 => Array
('id' => 474,
'pid' => 473,
 	     'name' => "primary_expression"
),
475 => Array
('id' => 475,
'pid' => 474,
 	     'name' => "i"
),
476 => Array
('id' => 476,
'pid' => 457,
 	     'name' => ")"
),
477 => Array
('id' => 477,
'pid' => 457,
 	     'name' => "block"
),
478 => Array
('id' => 478,
'pid' => 477,
 	     'name' => "{"
),
479 => Array
('id' => 479,
'pid' => 477,
 	     'name' => "statement_list"
),
480 => Array
('id' => 480,
'pid' => 479,
 	     'name' => "statement"
),
481 => Array
('id' => 481,
'pid' => 480,
 	     'name' => "expression"
),
482 => Array
('id' => 482,
'pid' => 481,
 	     'name' => "assignment_expression"
),
483 => Array
('id' => 483,
'pid' => 482,
 	     'name' => "logical_or_expression"
),
484 => Array
('id' => 484,
'pid' => 483,
 	     'name' => "logical_and_expression"
),
485 => Array
('id' => 485,
'pid' => 484,
 	     'name' => "equality_expression"
),
486 => Array
('id' => 486,
'pid' => 485,
 	     'name' => "relation_expression"
),
487 => Array
('id' => 487,
'pid' => 486,
 	     'name' => "additive_expression"
),
488 => Array
('id' => 488,
'pid' => 487,
 	     'name' => "multiplicative_expression"
),
489 => Array
('id' => 489,
'pid' => 488,
 	     'name' => "unary_expression"
),
490 => Array
('id' => 490,
'pid' => 489,
 	     'name' => "postfix_expression"
),
491 => Array
('id' => 491,
'pid' => 490,
 	     'name' => "primary_expression"
),
492 => Array
('id' => 492,
'pid' => 491,
 	     'name' => "i"
),
493 => Array
('id' => 493,
'pid' => 480,
 	     'name' => ";"
),
494 => Array
('id' => 494,
'pid' => 477,
 	     'name' => "}"
),
495 => Array
('id' => 495,
'pid' => 317,
 	     'name' => "statement"
),
496 => Array
('id' => 496,
'pid' => 495,
 	     'name' => "return_statement"
),
497 => Array
('id' => 497,
'pid' => 496,
 	     'name' => "return"
),
498 => Array
('id' => 498,
'pid' => 496,
 	     'name' => "expression_opt"
),
499 => Array
('id' => 499,
'pid' => 498,
 	     'name' => "expression"
),
500 => Array
('id' => 500,
'pid' => 499,
 	     'name' => "assignment_expression"
),
501 => Array
('id' => 501,
'pid' => 500,
 	     'name' => "logical_or_expression"
),
502 => Array
('id' => 502,
'pid' => 501,
 	     'name' => "logical_and_expression"
),
503 => Array
('id' => 503,
'pid' => 502,
 	     'name' => "equality_expression"
),
504 => Array
('id' => 504,
'pid' => 503,
 	     'name' => "relation_expression"
),
505 => Array
('id' => 505,
'pid' => 504,
 	     'name' => "additive_expression"
),
506 => Array
('id' => 506,
'pid' => 505,
 	     'name' => "multiplicative_expression"
),
507 => Array
('id' => 507,
'pid' => 506,
 	     'name' => "unary_expression"
),
508 => Array
('id' => 508,
'pid' => 507,
 	     'name' => "postfix_expression"
),
509 => Array
('id' => 509,
'pid' => 508,
 	     'name' => "primary_expression"
),
510 => Array
('id' => 510,
'pid' => 509,
 	     'name' => "b"
),
511 => Array
('id' => 511,
'pid' => 496,
 	     'name' => ";"
),
512 => Array
('id' => 512,
'pid' => 315,
 	     'name' => "}"
),
);
if('org_select' == $_POST['action']){
                  returnArray($result);
}
?>