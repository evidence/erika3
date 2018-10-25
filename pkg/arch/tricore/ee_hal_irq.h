/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 - 2018 Evidence s.r.l.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License, version 2, for more details.
 * 
 * You should have received a copy of the GNU General Public License,
 * version 2, along with this program; if not, see
 * < www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
 * 
 * This program is distributed to you subject to the following
 * clarifications and special exceptions to the GNU General Public
 * License, version 2.
 * 
 * THIRD PARTIES' MATERIALS
 * 
 * Certain materials included in this library are provided by third
 * parties under licenses other than the GNU General Public License. You
 * may only use, copy, link to, modify and redistribute this library
 * following the terms of license indicated below for third parties'
 * materials.
 * 
 * In case you make modified versions of this library which still include
 * said third parties' materials, you are obligated to grant this special
 * exception.
 * 
 * The complete list of Third party materials allowed with ERIKA
 * Enterprise version 3, together with the terms and conditions of each
 * license, is present in the file THIRDPARTY.TXT in the root of the
 * project.
 * ###*E*### */

/** \file   ee_hal_irq.h
 *  \brief  HAL for interrupt vector handling.
 *
 *  \author Errico Guidieri
 *  \date   2017
 */
#ifndef OSEE_HAL_IRQ_H
#define OSEE_HAL_IRQ_H

#include "ee_cfg.h"

/* ISR priority level defines: The value of these macros can be used in
   assembly inline templates, so no parentheses nor unsigned specifiers is
   allowed */
#define OSEE_ISR_UNMASKED 0
#define OSEE_ISR_PRI_1 1
#define OSEE_ISR_PRI_2 2
#define OSEE_ISR_PRI_3 3
#define OSEE_ISR_PRI_4 4
#define OSEE_ISR_PRI_5 5
#define OSEE_ISR_PRI_6 6
#define OSEE_ISR_PRI_7 7
#define OSEE_ISR_PRI_8 8
#define OSEE_ISR_PRI_9 9
#define OSEE_ISR_PRI_10 10
#define OSEE_ISR_PRI_11 11
#define OSEE_ISR_PRI_12 12
#define OSEE_ISR_PRI_13 13
#define OSEE_ISR_PRI_14 14
#define OSEE_ISR_PRI_15 15
#define OSEE_ISR_PRI_16 16
#define OSEE_ISR_PRI_17 17
#define OSEE_ISR_PRI_18 18
#define OSEE_ISR_PRI_19 19
#define OSEE_ISR_PRI_20 20
#define OSEE_ISR_PRI_21 21
#define OSEE_ISR_PRI_22 22
#define OSEE_ISR_PRI_23 23
#define OSEE_ISR_PRI_24 24
#define OSEE_ISR_PRI_25 25
#define OSEE_ISR_PRI_26 26
#define OSEE_ISR_PRI_27 27
#define OSEE_ISR_PRI_28 28
#define OSEE_ISR_PRI_29 29
#define OSEE_ISR_PRI_30 30
#define OSEE_ISR_PRI_31 31
#define OSEE_ISR_PRI_32 32
#define OSEE_ISR_PRI_33 33
#define OSEE_ISR_PRI_34 34
#define OSEE_ISR_PRI_35 35
#define OSEE_ISR_PRI_36 36
#define OSEE_ISR_PRI_37 37
#define OSEE_ISR_PRI_38 38
#define OSEE_ISR_PRI_39 39
#define OSEE_ISR_PRI_40 40
#define OSEE_ISR_PRI_41 41
#define OSEE_ISR_PRI_42 42
#define OSEE_ISR_PRI_43 43
#define OSEE_ISR_PRI_44 44
#define OSEE_ISR_PRI_45 45
#define OSEE_ISR_PRI_46 46
#define OSEE_ISR_PRI_47 47
#define OSEE_ISR_PRI_48 48
#define OSEE_ISR_PRI_49 49
#define OSEE_ISR_PRI_50 50
#define OSEE_ISR_PRI_51 51
#define OSEE_ISR_PRI_52 52
#define OSEE_ISR_PRI_53 53
#define OSEE_ISR_PRI_54 54
#define OSEE_ISR_PRI_55 55
#define OSEE_ISR_PRI_56 56
#define OSEE_ISR_PRI_57 57
#define OSEE_ISR_PRI_58 58
#define OSEE_ISR_PRI_59 59
#define OSEE_ISR_PRI_60 60
#define OSEE_ISR_PRI_61 61
#define OSEE_ISR_PRI_62 62
#define OSEE_ISR_PRI_63 63
#define OSEE_ISR_PRI_64 64
#define OSEE_ISR_PRI_65 65
#define OSEE_ISR_PRI_66 66
#define OSEE_ISR_PRI_67 67
#define OSEE_ISR_PRI_68 68
#define OSEE_ISR_PRI_69 69
#define OSEE_ISR_PRI_70 70
#define OSEE_ISR_PRI_71 71
#define OSEE_ISR_PRI_72 72
#define OSEE_ISR_PRI_73 73
#define OSEE_ISR_PRI_74 74
#define OSEE_ISR_PRI_75 75
#define OSEE_ISR_PRI_76 76
#define OSEE_ISR_PRI_77 77
#define OSEE_ISR_PRI_78 78
#define OSEE_ISR_PRI_79 79
#define OSEE_ISR_PRI_80 80
#define OSEE_ISR_PRI_81 81
#define OSEE_ISR_PRI_82 82
#define OSEE_ISR_PRI_83 83
#define OSEE_ISR_PRI_84 84
#define OSEE_ISR_PRI_85 85
#define OSEE_ISR_PRI_86 86
#define OSEE_ISR_PRI_87 87
#define OSEE_ISR_PRI_88 88
#define OSEE_ISR_PRI_89 89
#define OSEE_ISR_PRI_90 90
#define OSEE_ISR_PRI_91 91
#define OSEE_ISR_PRI_92 92
#define OSEE_ISR_PRI_93 93
#define OSEE_ISR_PRI_94 94
#define OSEE_ISR_PRI_95 95
#define OSEE_ISR_PRI_96 96
#define OSEE_ISR_PRI_97 97
#define OSEE_ISR_PRI_98 98
#define OSEE_ISR_PRI_99 99
#define OSEE_ISR_PRI_100 100
#define OSEE_ISR_PRI_101 101
#define OSEE_ISR_PRI_102 102
#define OSEE_ISR_PRI_103 103
#define OSEE_ISR_PRI_104 104
#define OSEE_ISR_PRI_105 105
#define OSEE_ISR_PRI_106 106
#define OSEE_ISR_PRI_107 107
#define OSEE_ISR_PRI_108 108
#define OSEE_ISR_PRI_109 109
#define OSEE_ISR_PRI_110 110
#define OSEE_ISR_PRI_111 111
#define OSEE_ISR_PRI_112 112
#define OSEE_ISR_PRI_113 113
#define OSEE_ISR_PRI_114 114
#define OSEE_ISR_PRI_115 115
#define OSEE_ISR_PRI_116 116
#define OSEE_ISR_PRI_117 117
#define OSEE_ISR_PRI_118 118
#define OSEE_ISR_PRI_119 119
#define OSEE_ISR_PRI_120 120
#define OSEE_ISR_PRI_121 121
#define OSEE_ISR_PRI_122 122
#define OSEE_ISR_PRI_123 123
#define OSEE_ISR_PRI_124 124
#define OSEE_ISR_PRI_125 125
#define OSEE_ISR_PRI_126 126
#define OSEE_ISR_PRI_127 127
#define OSEE_ISR_PRI_128 128
#define OSEE_ISR_PRI_129 129
#define OSEE_ISR_PRI_130 130
#define OSEE_ISR_PRI_131 131
#define OSEE_ISR_PRI_132 132
#define OSEE_ISR_PRI_133 133
#define OSEE_ISR_PRI_134 134
#define OSEE_ISR_PRI_135 135
#define OSEE_ISR_PRI_136 136
#define OSEE_ISR_PRI_137 137
#define OSEE_ISR_PRI_138 138
#define OSEE_ISR_PRI_139 139
#define OSEE_ISR_PRI_140 140
#define OSEE_ISR_PRI_141 141
#define OSEE_ISR_PRI_142 142
#define OSEE_ISR_PRI_143 143
#define OSEE_ISR_PRI_144 144
#define OSEE_ISR_PRI_145 145
#define OSEE_ISR_PRI_146 146
#define OSEE_ISR_PRI_147 147
#define OSEE_ISR_PRI_148 148
#define OSEE_ISR_PRI_149 149
#define OSEE_ISR_PRI_150 150
#define OSEE_ISR_PRI_151 151
#define OSEE_ISR_PRI_152 152
#define OSEE_ISR_PRI_153 153
#define OSEE_ISR_PRI_154 154
#define OSEE_ISR_PRI_155 155
#define OSEE_ISR_PRI_156 156
#define OSEE_ISR_PRI_157 157
#define OSEE_ISR_PRI_158 158
#define OSEE_ISR_PRI_159 159
#define OSEE_ISR_PRI_160 160
#define OSEE_ISR_PRI_161 161
#define OSEE_ISR_PRI_162 162
#define OSEE_ISR_PRI_163 163
#define OSEE_ISR_PRI_164 164
#define OSEE_ISR_PRI_165 165
#define OSEE_ISR_PRI_166 166
#define OSEE_ISR_PRI_167 167
#define OSEE_ISR_PRI_168 168
#define OSEE_ISR_PRI_169 169
#define OSEE_ISR_PRI_170 170
#define OSEE_ISR_PRI_171 171
#define OSEE_ISR_PRI_172 172
#define OSEE_ISR_PRI_173 173
#define OSEE_ISR_PRI_174 174
#define OSEE_ISR_PRI_175 175
#define OSEE_ISR_PRI_176 176
#define OSEE_ISR_PRI_177 177
#define OSEE_ISR_PRI_178 178
#define OSEE_ISR_PRI_179 179
#define OSEE_ISR_PRI_180 180
#define OSEE_ISR_PRI_181 181
#define OSEE_ISR_PRI_182 182
#define OSEE_ISR_PRI_183 183
#define OSEE_ISR_PRI_184 184
#define OSEE_ISR_PRI_185 185
#define OSEE_ISR_PRI_186 186
#define OSEE_ISR_PRI_187 187
#define OSEE_ISR_PRI_188 188
#define OSEE_ISR_PRI_189 189
#define OSEE_ISR_PRI_190 190
#define OSEE_ISR_PRI_191 191
#define OSEE_ISR_PRI_192 192
#define OSEE_ISR_PRI_193 193
#define OSEE_ISR_PRI_194 194
#define OSEE_ISR_PRI_195 195
#define OSEE_ISR_PRI_196 196
#define OSEE_ISR_PRI_197 197
#define OSEE_ISR_PRI_198 198
#define OSEE_ISR_PRI_199 199
#define OSEE_ISR_PRI_200 200
#define OSEE_ISR_PRI_201 201
#define OSEE_ISR_PRI_202 202
#define OSEE_ISR_PRI_203 203
#define OSEE_ISR_PRI_204 204
#define OSEE_ISR_PRI_205 205
#define OSEE_ISR_PRI_206 206
#define OSEE_ISR_PRI_207 207
#define OSEE_ISR_PRI_208 208
#define OSEE_ISR_PRI_209 209
#define OSEE_ISR_PRI_210 210
#define OSEE_ISR_PRI_211 211
#define OSEE_ISR_PRI_212 212
#define OSEE_ISR_PRI_213 213
#define OSEE_ISR_PRI_214 214
#define OSEE_ISR_PRI_215 215
#define OSEE_ISR_PRI_216 216
#define OSEE_ISR_PRI_217 217
#define OSEE_ISR_PRI_218 218
#define OSEE_ISR_PRI_219 219
#define OSEE_ISR_PRI_220 220
#define OSEE_ISR_PRI_221 221
#define OSEE_ISR_PRI_222 222
#define OSEE_ISR_PRI_223 223
#define OSEE_ISR_PRI_224 224
#define OSEE_ISR_PRI_225 225
#define OSEE_ISR_PRI_226 226
#define OSEE_ISR_PRI_227 227
#define OSEE_ISR_PRI_228 228
#define OSEE_ISR_PRI_229 229
#define OSEE_ISR_PRI_230 230
#define OSEE_ISR_PRI_231 231
#define OSEE_ISR_PRI_232 232
#define OSEE_ISR_PRI_233 233
#define OSEE_ISR_PRI_234 234
#define OSEE_ISR_PRI_235 235
#define OSEE_ISR_PRI_236 236
#define OSEE_ISR_PRI_237 237
#define OSEE_ISR_PRI_238 238
#define OSEE_ISR_PRI_239 239
#define OSEE_ISR_PRI_240 240
#define OSEE_ISR_PRI_241 241
#define OSEE_ISR_PRI_242 242
#define OSEE_ISR_PRI_243 243
#define OSEE_ISR_PRI_244 244
#define OSEE_ISR_PRI_245 245
#define OSEE_ISR_PRI_246 246
#define OSEE_ISR_PRI_247 247
#define OSEE_ISR_PRI_248 248
#define OSEE_ISR_PRI_249 249
#define OSEE_ISR_PRI_250 250
#define OSEE_ISR_PRI_251 251
#define OSEE_ISR_PRI_252 252
#define OSEE_ISR_PRI_253 253
#define OSEE_ISR_PRI_254 254
#define OSEE_ISR_PRI_255 255

#if (!defined(ISR))
#define ISR(f) void f(void)
#endif /* !ISR */

#if (!defined(ISR1))
#define ISR1 ISR
#endif /* !ISR1 */

#if (!defined(ISR2))
#define ISR2 ISR
#endif /* !ISR2 */

#if (defined(OSEE_HAS_SYSTEM_TIMER))
extern void osEE_tricore_system_timer_handler(void);
#endif /* OSEE_HAS_SYSTEM_TIMER */

#endif /* OSEE_HAL_IRQ_H */
