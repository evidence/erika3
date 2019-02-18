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
#define OSEE_ISR_UNMASKED 0  /**< ISR Priority - unmasked */
#define OSEE_ISR_PRI_1 1     /**< ISR Priority 20 */
#define OSEE_ISR_PRI_2 2     /**< ISR Priority 20 */
#define OSEE_ISR_PRI_3 3     /**< ISR Priority 20 */
#define OSEE_ISR_PRI_4 4     /**< ISR Priority 20 */
#define OSEE_ISR_PRI_5 5     /**< ISR Priority 20 */
#define OSEE_ISR_PRI_6 6     /**< ISR Priority 20 */
#define OSEE_ISR_PRI_7 7     /**< ISR Priority 20 */
#define OSEE_ISR_PRI_8 8     /**< ISR Priority 20 */
#define OSEE_ISR_PRI_9 9     /**< ISR Priority 20 */
#define OSEE_ISR_PRI_10 10   /**< ISR Priority 20 */
#define OSEE_ISR_PRI_11 11   /**< ISR Priority 20 */
#define OSEE_ISR_PRI_12 12   /**< ISR Priority 20 */
#define OSEE_ISR_PRI_13 13   /**< ISR Priority 20 */
#define OSEE_ISR_PRI_14 14   /**< ISR Priority 20 */
#define OSEE_ISR_PRI_15 15   /**< ISR Priority 20 */
#define OSEE_ISR_PRI_16 16   /**< ISR Priority 16 */
#define OSEE_ISR_PRI_17 17   /**< ISR Priority 17 */
#define OSEE_ISR_PRI_18 18   /**< ISR Priority 18 */
#define OSEE_ISR_PRI_19 19   /**< ISR Priority 19 */
#define OSEE_ISR_PRI_20 20   /**< ISR Priority 20 */
#define OSEE_ISR_PRI_21 21   /**< ISR Priority 21 */
#define OSEE_ISR_PRI_22 22   /**< ISR Priority 22 */
#define OSEE_ISR_PRI_23 23   /**< ISR Priority 23 */
#define OSEE_ISR_PRI_24 24   /**< ISR Priority 24 */
#define OSEE_ISR_PRI_25 25   /**< ISR Priority 25 */
#define OSEE_ISR_PRI_26 26   /**< ISR Priority 26 */
#define OSEE_ISR_PRI_27 27   /**< ISR Priority 27 */
#define OSEE_ISR_PRI_28 28   /**< ISR Priority 28 */
#define OSEE_ISR_PRI_29 29   /**< ISR Priority 29 */
#define OSEE_ISR_PRI_30 30   /**< ISR Priority 30 */
#define OSEE_ISR_PRI_31 31   /**< ISR Priority 31 */
#define OSEE_ISR_PRI_32 32   /**< ISR Priority 32 */
#define OSEE_ISR_PRI_33 33   /**< ISR Priority 33 */
#define OSEE_ISR_PRI_34 34   /**< ISR Priority 34 */
#define OSEE_ISR_PRI_35 35   /**< ISR Priority 35 */
#define OSEE_ISR_PRI_36 36   /**< ISR Priority 36 */
#define OSEE_ISR_PRI_37 37   /**< ISR Priority 37 */
#define OSEE_ISR_PRI_38 38   /**< ISR Priority 38 */
#define OSEE_ISR_PRI_39 39   /**< ISR Priority 39 */
#define OSEE_ISR_PRI_40 40   /**< ISR Priority 40 */
#define OSEE_ISR_PRI_41 41   /**< ISR Priority 41 */
#define OSEE_ISR_PRI_42 42   /**< ISR Priority 42 */
#define OSEE_ISR_PRI_43 43   /**< ISR Priority 43 */
#define OSEE_ISR_PRI_44 44   /**< ISR Priority 44 */
#define OSEE_ISR_PRI_45 45   /**< ISR Priority 45 */
#define OSEE_ISR_PRI_46 46   /**< ISR Priority 46 */
#define OSEE_ISR_PRI_47 47   /**< ISR Priority 47 */
#define OSEE_ISR_PRI_48 48   /**< ISR Priority 48 */
#define OSEE_ISR_PRI_49 49   /**< ISR Priority 49 */
#define OSEE_ISR_PRI_50 50   /**< ISR Priority 50 */
#define OSEE_ISR_PRI_51 51   /**< ISR Priority 51 */
#define OSEE_ISR_PRI_52 52   /**< ISR Priority 52 */
#define OSEE_ISR_PRI_53 53   /**< ISR Priority 53 */
#define OSEE_ISR_PRI_54 54   /**< ISR Priority 54 */
#define OSEE_ISR_PRI_55 55   /**< ISR Priority 55 */
#define OSEE_ISR_PRI_56 56   /**< ISR Priority 56 */
#define OSEE_ISR_PRI_57 57   /**< ISR Priority 57 */
#define OSEE_ISR_PRI_58 58   /**< ISR Priority 58 */
#define OSEE_ISR_PRI_59 59   /**< ISR Priority 59 */
#define OSEE_ISR_PRI_60 60   /**< ISR Priority 60 */
#define OSEE_ISR_PRI_61 61   /**< ISR Priority 61 */
#define OSEE_ISR_PRI_62 62   /**< ISR Priority 62 */
#define OSEE_ISR_PRI_63 63   /**< ISR Priority 63 */
#define OSEE_ISR_PRI_64 64   /**< ISR Priority 64 */
#define OSEE_ISR_PRI_65 65   /**< ISR Priority 65 */
#define OSEE_ISR_PRI_66 66   /**< ISR Priority 66 */
#define OSEE_ISR_PRI_67 67   /**< ISR Priority 67 */
#define OSEE_ISR_PRI_68 68   /**< ISR Priority 68 */
#define OSEE_ISR_PRI_69 69   /**< ISR Priority 69 */
#define OSEE_ISR_PRI_70 70   /**< ISR Priority 70 */
#define OSEE_ISR_PRI_71 71   /**< ISR Priority 71 */
#define OSEE_ISR_PRI_72 72   /**< ISR Priority 72 */
#define OSEE_ISR_PRI_73 73   /**< ISR Priority 73 */
#define OSEE_ISR_PRI_74 74   /**< ISR Priority 74 */
#define OSEE_ISR_PRI_75 75   /**< ISR Priority 75 */
#define OSEE_ISR_PRI_76 76   /**< ISR Priority 76 */
#define OSEE_ISR_PRI_77 77   /**< ISR Priority 77 */
#define OSEE_ISR_PRI_78 78   /**< ISR Priority 78 */
#define OSEE_ISR_PRI_79 79   /**< ISR Priority 79 */
#define OSEE_ISR_PRI_80 80   /**< ISR Priority 80 */
#define OSEE_ISR_PRI_81 81   /**< ISR Priority 81 */
#define OSEE_ISR_PRI_82 82   /**< ISR Priority 82 */
#define OSEE_ISR_PRI_83 83   /**< ISR Priority 83 */
#define OSEE_ISR_PRI_84 84   /**< ISR Priority 84 */
#define OSEE_ISR_PRI_85 85   /**< ISR Priority 85 */
#define OSEE_ISR_PRI_86 86   /**< ISR Priority 86 */
#define OSEE_ISR_PRI_87 87   /**< ISR Priority 87 */
#define OSEE_ISR_PRI_88 88   /**< ISR Priority 88 */
#define OSEE_ISR_PRI_89 89   /**< ISR Priority 89 */
#define OSEE_ISR_PRI_90 90   /**< ISR Priority 90 */
#define OSEE_ISR_PRI_91 91   /**< ISR Priority 91 */
#define OSEE_ISR_PRI_92 92   /**< ISR Priority 92 */
#define OSEE_ISR_PRI_93 93   /**< ISR Priority 93 */
#define OSEE_ISR_PRI_94 94   /**< ISR Priority 94 */
#define OSEE_ISR_PRI_95 95   /**< ISR Priority 95 */
#define OSEE_ISR_PRI_96 96   /**< ISR Priority 96 */
#define OSEE_ISR_PRI_97 97   /**< ISR Priority 97 */
#define OSEE_ISR_PRI_98 98   /**< ISR Priority 98 */
#define OSEE_ISR_PRI_99 99   /**< ISR Priority 99 */
#define OSEE_ISR_PRI_100 100 /**< ISR Priority 100 */
#define OSEE_ISR_PRI_101 101 /**< ISR Priority 101 */
#define OSEE_ISR_PRI_102 102 /**< ISR Priority 102 */
#define OSEE_ISR_PRI_103 103 /**< ISR Priority 103 */
#define OSEE_ISR_PRI_104 104 /**< ISR Priority 104 */
#define OSEE_ISR_PRI_105 105 /**< ISR Priority 105 */
#define OSEE_ISR_PRI_106 106 /**< ISR Priority 106 */
#define OSEE_ISR_PRI_107 107 /**< ISR Priority 107 */
#define OSEE_ISR_PRI_108 108 /**< ISR Priority 108 */
#define OSEE_ISR_PRI_109 109 /**< ISR Priority 109 */
#define OSEE_ISR_PRI_110 110 /**< ISR Priority 110 */
#define OSEE_ISR_PRI_111 111 /**< ISR Priority 111 */
#define OSEE_ISR_PRI_112 112 /**< ISR Priority 112 */
#define OSEE_ISR_PRI_113 113 /**< ISR Priority 113 */
#define OSEE_ISR_PRI_114 114 /**< ISR Priority 114 */
#define OSEE_ISR_PRI_115 115 /**< ISR Priority 115 */
#define OSEE_ISR_PRI_116 116 /**< ISR Priority 116 */
#define OSEE_ISR_PRI_117 117 /**< ISR Priority 117 */
#define OSEE_ISR_PRI_118 118 /**< ISR Priority 118 */
#define OSEE_ISR_PRI_119 119 /**< ISR Priority 119 */
#define OSEE_ISR_PRI_120 120 /**< ISR Priority 120 */
#define OSEE_ISR_PRI_121 121 /**< ISR Priority 121 */
#define OSEE_ISR_PRI_122 122 /**< ISR Priority 122 */
#define OSEE_ISR_PRI_123 123 /**< ISR Priority 123 */
#define OSEE_ISR_PRI_124 124 /**< ISR Priority 124 */
#define OSEE_ISR_PRI_125 125 /**< ISR Priority 125 */
#define OSEE_ISR_PRI_126 126 /**< ISR Priority 126 */
#define OSEE_ISR_PRI_127 127 /**< ISR Priority 127 */
#define OSEE_ISR_PRI_128 128 /**< ISR Priority 128 */
#define OSEE_ISR_PRI_129 129 /**< ISR Priority 129 */
#define OSEE_ISR_PRI_130 130 /**< ISR Priority 130 */
#define OSEE_ISR_PRI_131 131 /**< ISR Priority 131 */
#define OSEE_ISR_PRI_132 132 /**< ISR Priority 132 */
#define OSEE_ISR_PRI_133 133 /**< ISR Priority 133 */
#define OSEE_ISR_PRI_134 134 /**< ISR Priority 134 */
#define OSEE_ISR_PRI_135 135 /**< ISR Priority 135 */
#define OSEE_ISR_PRI_136 136 /**< ISR Priority 136 */
#define OSEE_ISR_PRI_137 137 /**< ISR Priority 137 */
#define OSEE_ISR_PRI_138 138 /**< ISR Priority 138 */
#define OSEE_ISR_PRI_139 139 /**< ISR Priority 139 */
#define OSEE_ISR_PRI_140 140 /**< ISR Priority 140 */
#define OSEE_ISR_PRI_141 141 /**< ISR Priority 141 */
#define OSEE_ISR_PRI_142 142 /**< ISR Priority 142 */
#define OSEE_ISR_PRI_143 143 /**< ISR Priority 143 */
#define OSEE_ISR_PRI_144 144 /**< ISR Priority 144 */
#define OSEE_ISR_PRI_145 145 /**< ISR Priority 145 */
#define OSEE_ISR_PRI_146 146 /**< ISR Priority 146 */
#define OSEE_ISR_PRI_147 147 /**< ISR Priority 147 */
#define OSEE_ISR_PRI_148 148 /**< ISR Priority 148 */
#define OSEE_ISR_PRI_149 149 /**< ISR Priority 149 */
#define OSEE_ISR_PRI_150 150 /**< ISR Priority 150 */
#define OSEE_ISR_PRI_151 151 /**< ISR Priority 151 */
#define OSEE_ISR_PRI_152 152 /**< ISR Priority 152 */
#define OSEE_ISR_PRI_153 153 /**< ISR Priority 153 */
#define OSEE_ISR_PRI_154 154 /**< ISR Priority 154 */
#define OSEE_ISR_PRI_155 155 /**< ISR Priority 155 */
#define OSEE_ISR_PRI_156 156 /**< ISR Priority 156 */
#define OSEE_ISR_PRI_157 157 /**< ISR Priority 157 */
#define OSEE_ISR_PRI_158 158 /**< ISR Priority 158 */
#define OSEE_ISR_PRI_159 159 /**< ISR Priority 159 */
#define OSEE_ISR_PRI_160 160 /**< ISR Priority 160 */
#define OSEE_ISR_PRI_161 161 /**< ISR Priority 161 */
#define OSEE_ISR_PRI_162 162 /**< ISR Priority 162 */
#define OSEE_ISR_PRI_163 163 /**< ISR Priority 163 */
#define OSEE_ISR_PRI_164 164 /**< ISR Priority 164 */
#define OSEE_ISR_PRI_165 165 /**< ISR Priority 165 */
#define OSEE_ISR_PRI_166 166 /**< ISR Priority 166 */
#define OSEE_ISR_PRI_167 167 /**< ISR Priority 167 */
#define OSEE_ISR_PRI_168 168 /**< ISR Priority 168 */
#define OSEE_ISR_PRI_169 169 /**< ISR Priority 169 */
#define OSEE_ISR_PRI_170 170 /**< ISR Priority 170 */
#define OSEE_ISR_PRI_171 171 /**< ISR Priority 171 */
#define OSEE_ISR_PRI_172 172 /**< ISR Priority 172 */
#define OSEE_ISR_PRI_173 173 /**< ISR Priority 173 */
#define OSEE_ISR_PRI_174 174 /**< ISR Priority 174 */
#define OSEE_ISR_PRI_175 175 /**< ISR Priority 175 */
#define OSEE_ISR_PRI_176 176 /**< ISR Priority 176 */
#define OSEE_ISR_PRI_177 177 /**< ISR Priority 177 */
#define OSEE_ISR_PRI_178 178 /**< ISR Priority 178 */
#define OSEE_ISR_PRI_179 179 /**< ISR Priority 179 */
#define OSEE_ISR_PRI_180 180 /**< ISR Priority 180 */
#define OSEE_ISR_PRI_181 181 /**< ISR Priority 181 */
#define OSEE_ISR_PRI_182 182 /**< ISR Priority 182 */
#define OSEE_ISR_PRI_183 183 /**< ISR Priority 183 */
#define OSEE_ISR_PRI_184 184 /**< ISR Priority 184 */
#define OSEE_ISR_PRI_185 185 /**< ISR Priority 185 */
#define OSEE_ISR_PRI_186 186 /**< ISR Priority 186 */
#define OSEE_ISR_PRI_187 187 /**< ISR Priority 187 */
#define OSEE_ISR_PRI_188 188 /**< ISR Priority 188 */
#define OSEE_ISR_PRI_189 189 /**< ISR Priority 189 */
#define OSEE_ISR_PRI_190 190 /**< ISR Priority 190 */
#define OSEE_ISR_PRI_191 191 /**< ISR Priority 191 */
#define OSEE_ISR_PRI_192 192 /**< ISR Priority 192 */
#define OSEE_ISR_PRI_193 193 /**< ISR Priority 193 */
#define OSEE_ISR_PRI_194 194 /**< ISR Priority 194 */
#define OSEE_ISR_PRI_195 195 /**< ISR Priority 195 */
#define OSEE_ISR_PRI_196 196 /**< ISR Priority 196 */
#define OSEE_ISR_PRI_197 197 /**< ISR Priority 197 */
#define OSEE_ISR_PRI_198 198 /**< ISR Priority 198 */
#define OSEE_ISR_PRI_199 199 /**< ISR Priority 199 */
#define OSEE_ISR_PRI_200 200 /**< ISR Priority 200 */
#define OSEE_ISR_PRI_201 201 /**< ISR Priority 201 */
#define OSEE_ISR_PRI_202 202 /**< ISR Priority 202 */
#define OSEE_ISR_PRI_203 203 /**< ISR Priority 203 */
#define OSEE_ISR_PRI_204 204 /**< ISR Priority 204 */
#define OSEE_ISR_PRI_205 205 /**< ISR Priority 205 */
#define OSEE_ISR_PRI_206 206 /**< ISR Priority 206 */
#define OSEE_ISR_PRI_207 207 /**< ISR Priority 207 */
#define OSEE_ISR_PRI_208 208 /**< ISR Priority 208 */
#define OSEE_ISR_PRI_209 209 /**< ISR Priority 209 */
#define OSEE_ISR_PRI_210 210 /**< ISR Priority 210 */
#define OSEE_ISR_PRI_211 211 /**< ISR Priority 211 */
#define OSEE_ISR_PRI_212 212 /**< ISR Priority 212 */
#define OSEE_ISR_PRI_213 213 /**< ISR Priority 213 */
#define OSEE_ISR_PRI_214 214 /**< ISR Priority 214 */
#define OSEE_ISR_PRI_215 215 /**< ISR Priority 215 */
#define OSEE_ISR_PRI_216 216 /**< ISR Priority 216 */
#define OSEE_ISR_PRI_217 217 /**< ISR Priority 217 */
#define OSEE_ISR_PRI_218 218 /**< ISR Priority 218 */
#define OSEE_ISR_PRI_219 219 /**< ISR Priority 219 */
#define OSEE_ISR_PRI_220 220 /**< ISR Priority 220 */
#define OSEE_ISR_PRI_221 221 /**< ISR Priority 221 */
#define OSEE_ISR_PRI_222 222 /**< ISR Priority 222 */
#define OSEE_ISR_PRI_223 223 /**< ISR Priority 223 */
#define OSEE_ISR_PRI_224 224 /**< ISR Priority 224 */
#define OSEE_ISR_PRI_225 225 /**< ISR Priority 225 */
#define OSEE_ISR_PRI_226 226 /**< ISR Priority 226 */
#define OSEE_ISR_PRI_227 227 /**< ISR Priority 227 */
#define OSEE_ISR_PRI_228 228 /**< ISR Priority 228 */
#define OSEE_ISR_PRI_229 229 /**< ISR Priority 229 */
#define OSEE_ISR_PRI_230 230 /**< ISR Priority 230 */
#define OSEE_ISR_PRI_231 231 /**< ISR Priority 231 */
#define OSEE_ISR_PRI_232 232 /**< ISR Priority 232 */
#define OSEE_ISR_PRI_233 233 /**< ISR Priority 233 */
#define OSEE_ISR_PRI_234 234 /**< ISR Priority 234 */
#define OSEE_ISR_PRI_235 235 /**< ISR Priority 235 */
#define OSEE_ISR_PRI_236 236 /**< ISR Priority 236 */
#define OSEE_ISR_PRI_237 237 /**< ISR Priority 237 */
#define OSEE_ISR_PRI_238 238 /**< ISR Priority 238 */
#define OSEE_ISR_PRI_239 239 /**< ISR Priority 239 */
#define OSEE_ISR_PRI_240 240 /**< ISR Priority 240 */
#define OSEE_ISR_PRI_241 241 /**< ISR Priority 241 */
#define OSEE_ISR_PRI_242 242 /**< ISR Priority 242 */
#define OSEE_ISR_PRI_243 243 /**< ISR Priority 243 */
#define OSEE_ISR_PRI_244 244 /**< ISR Priority 244 */
#define OSEE_ISR_PRI_245 245 /**< ISR Priority 245 */
#define OSEE_ISR_PRI_246 246 /**< ISR Priority 246 */
#define OSEE_ISR_PRI_247 247 /**< ISR Priority 247 */
#define OSEE_ISR_PRI_248 248 /**< ISR Priority 248 */
#define OSEE_ISR_PRI_249 249 /**< ISR Priority 249 */
#define OSEE_ISR_PRI_250 250 /**< ISR Priority 250 */
#define OSEE_ISR_PRI_251 251 /**< ISR Priority 251 */
#define OSEE_ISR_PRI_252 252 /**< ISR Priority 252 */
#define OSEE_ISR_PRI_253 253 /**< ISR Priority 253 */
#define OSEE_ISR_PRI_254 254 /**< ISR Priority 254 */
#define OSEE_ISR_PRI_255 255 /**< ISR Priority 255 */

#if (!defined(ISR))
/**
 *  \brief Declaration of an interrupt function Category 2.
 *  \ingroup primitives-interrupt
 *
 *  Declaration of an interrupt function Category 2.
 *  
 *  Reference:  OSEK OS - ISO 17356-3 - 13.4.3
 *  
 *  \param [in] f The interrupt handler
 */
#define ISR(f) void f(void)
#endif /* !ISR */

#if (!defined(ISR1))
/**
 *  \brief Declaration of an interrupt function Category 1.
 *  \ingroup primitives-interrupt
 *
 *  Declaration of an interrupt function Category 1.
 *  This is an extension of the standard ISR() macro.
 *  
 *  Reference:  OSEK OS - ISO 17356-3 - 13.4.3
 */
#define ISR1 ISR
#endif /* !ISR1 */

#if (!defined(ISR2))
/**
 *  \brief Declaration of an interrupt function Category 2.
 *  \ingroup primitives-interrupt
 *
 *  Declaration of an interrupt function Category 2.
 *  This is an extension of the standard ISR() macro.
 *  
 *  Reference:  OSEK OS - ISO 17356-3 - 13.4.3
 */
#define ISR2 ISR
#endif /* !ISR2 */

#if (defined(OSEE_HAS_SYSTEM_TIMER))
extern void osEE_tricore_system_timer_handler(void);
#endif /* OSEE_HAS_SYSTEM_TIMER */

#endif /* OSEE_HAL_IRQ_H */

