// The MIT License (MIT)
//
// Copyright (c) 2020 Huimao Chen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef HMLog_h
#define HMLog_h

#import <UIKit/UIKit.h>

#pragma mark - Parameters

#ifndef HMLogEnable
#define HMLogEnable 1
#endif  // HMLogEnable

#ifndef HMPrintEnable
#define HMPrintEnable 1
#endif  // HMPrintEnable

#ifndef HMLogPrefix
#define HMLogPrefix(INDEX, VAR) HMStringify(INDEX: VAR =)
#endif  // HMLogPrefix

#ifndef HMLogHeaderFormatString
#define HMLogHeaderFormatString(FUNC, LINE) \
        [NSString stringWithFormat:@"================  %s [%d]  ================\n", FUNC, LINE]
#endif  // HMLogHeaderFormatString

#pragma mark - Core

// format, private macro
#define _HMLogFormat(INDEX, VAR) \
        , HMLogPrefix(INDEX, VAR), @encode(__typeof__(VAR)), (VAR)

// HMFormatString
#define HMFormatString(...) \
        _HMFormatString(HMArgCount(__VA_ARGS__), __LINE__, __func__ HMForeach(_HMLogFormat, __VA_ARGS__))

// HMLog
#if HMLogEnable
    #define HMLog(...) \
            _HMLog(HMFormatString(__VA_ARGS__))
#else
    #define HMLog(...)
#endif  //  HMLogEnable

// HMPrint
#if HMPrintEnable
    #define HMPrint(...) \
            _HMPrint(HMFormatString(__VA_ARGS__))
#else
    #define HMPrint(...)
#endif  //  HMPrintEnable


static inline NSString * _HMFormatString(int count, ...) { //  count, line, func, [index: var =, encode, var]
    NSMutableString *result = [[NSMutableString alloc] init];
    
    va_list v;
    va_start(v, count);
    
    //  handle header
    int line = va_arg(v, int);
    char *func = va_arg(v, char *);
    [result appendString:((void)(line), (void)(func), HMLogHeaderFormatString(func, line))];
    
    // handle arguments
    for (int i = 0; i < count; ++i) {
        char *prefix = va_arg(v, char *);
        char *type = va_arg(v, char *);
        
        id obj = nil;
        if (strcmp(type, @encode(id)) == 0) {   //  "@"   id
            id actual = va_arg(v, id);
            obj = actual;
            
        } else if (strcmp(type, @encode(CGPoint)) == 0) {           //  "{CGPoint=dd}"  CGPoint
            CGPoint actual = (CGPoint)va_arg(v, CGPoint);
            obj = [NSValue value:&actual withObjCType:type];
            
        } else if (strcmp(type, @encode(CGSize)) == 0) {            //  "{CGSize=dd}"   CGSize
            CGSize actual = (CGSize)va_arg(v, CGSize);
            obj = [NSValue value:&actual withObjCType:type];
            
        } else if (strcmp(type, @encode(CGRect)) == 0) {            //  "{CGRect={CGPoint=dd}{CGSize=dd}}"  CGRect
            CGRect actual = (CGRect)va_arg(v, CGRect);
            obj = [NSValue value:&actual withObjCType:type];
            
        } else if (strcmp(type, @encode(UIEdgeInsets)) == 0) {      //  "{UIEdgeInsets=dddd}"   UIEdgeInsets
            UIEdgeInsets actual = (UIEdgeInsets)va_arg(v, UIEdgeInsets);
            obj = NSStringFromUIEdgeInsets(actual);
            
        } else if (strcmp(type, @encode(NSRange)) == 0) {           //  "{_NSRange=QQ}" NSRange
            NSRange actual = (NSRange)va_arg(v, NSRange);
            obj = NSStringFromRange(actual);
            
        } else if (strcmp(type, @encode(SEL)) == 0) {               //  ":"     SEL
            SEL actual = (SEL)va_arg(v, SEL);
            obj = [NSString stringWithFormat:@"SEL: %@", NSStringFromSelector(actual)];
            
        } else if (strcmp(type, @encode(Class)) == 0) {             //  "#"     Class
            Class actual = (Class)va_arg(v, Class);
            obj = NSStringFromClass(actual);
            
        } else if (strcmp(type, @encode(double)) == 0) {            //  "d"     double
            double actual = (double)va_arg(v, double);
            obj = [NSNumber numberWithDouble:actual];
            
        } else if (strcmp(type, @encode(float)) == 0) {             //  "f"     float
            float actual = (float)va_arg(v, double);
            obj = [NSNumber numberWithFloat:actual];
            
        } else if (strcmp(type, @encode(int)) == 0) {               //  "i"     int
            int actual = (int)va_arg(v, int);
            obj = [NSNumber numberWithInt:actual];
            
        } else if (strcmp(type, @encode(long)) == 0) {              //  "q"     long
            long actual = (long)va_arg(v, long);
            obj = [NSNumber numberWithLong:actual];
            
        } else if (strcmp(type, @encode(long long)) == 0) {         //  "q"     long long
            long long actual = (long long)va_arg(v, long long);
            obj = [NSNumber numberWithLongLong:actual];
            
        } else if (strcmp(type, @encode(short)) == 0) {             //  "s"     short
            short actual = (short)va_arg(v, int);
            obj = [NSNumber numberWithShort:actual];
            
        } else if (strcmp(type, @encode(char)) == 0) {              //  "c"     char & BOOL(32bit)
            char actual = (char)va_arg(v, int);
            obj = [NSString stringWithFormat:@"%d char:%c", actual, actual];
            
        } else if (strcmp(type, @encode(bool)) == 0) {              //  "B"     bool & BOOL(64bit)
            bool actual = (bool)va_arg(v, int);
            obj = actual ? @"YES" : @"NO";
            
        } else if (strcmp(type, @encode(unsigned char)) == 0) {             //  "C"     unsigned char
            unsigned char actual = (unsigned char)va_arg(v, unsigned int);
            obj = [NSString stringWithFormat:@"%d unsigned char:%c", actual, actual];
            
        } else if (strcmp(type, @encode(unsigned int)) == 0) {              //  "I"     unsigned int
            unsigned int actual = (unsigned int)va_arg(v, unsigned int);
            obj = [NSNumber numberWithUnsignedInt:actual];
            
        } else if (strcmp(type, @encode(unsigned long)) == 0) {             //  "Q"     unsigned long
            unsigned long actual = (unsigned long)va_arg(v, unsigned long);
            obj = [NSNumber numberWithUnsignedLong:actual];
            
        } else if (strcmp(type, @encode(unsigned long long)) == 0) {        //  "Q"     unsigned long long
            unsigned long long actual = (unsigned long long)va_arg(v, unsigned long long);
            obj = [NSNumber numberWithUnsignedLongLong:actual];
            
        } else if (strcmp(type, @encode(unsigned short)) == 0) {            //  "S"     unsigned short
            unsigned short actual = (unsigned short)va_arg(v, unsigned int);
            obj = [NSNumber numberWithUnsignedShort:actual];
            
        } else {
            [result appendString:@"Error: unknown type"];
            break;
        }
        
        if (strlen(prefix) == 0) {
            [result appendFormat:@"%@\n", obj];
        } else {
            [result appendFormat:@"%s %@\n", prefix, obj];
        }
    }
    va_end(v);
    
    return [result copy];
}

static inline void _HMLog(NSString *str) {
    NSLog(@"\n%@", str);
}

static inline void _HMPrint(NSString *str) {
    printf("%s\n", str.UTF8String);
}

#pragma mark - Helper

/// Return a string representation of VALUE
#define HMStringify(VALUE) _HMStringify(VALUE)
#define _HMStringify(VALUE) # VALUE

/// Return a result of concatenating A and B
#define HMConcat(A, B) _HMConcat(A, B)
#define _HMConcat(A, B) A ## B

/// Return the number of arguments (up to twenty, at least one) provided to the macro.
#define HMArgCount(...) _HMArgCount(__VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define _HMArgCount(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, COUNT, ...) COUNT

/// Each argument will be passed to the MACRO, the MACRO must be this form: MACRO(index, arg). Inspired by https://github.com/jspahrsummers/libextobjc/blob/master/extobjc/metamacros.h
#define HMForeach(MACRO, ...) _HMForeach(MACRO, HMConcat(_HMForeach, HMArgCount(__VA_ARGS__)), __VA_ARGS__)
#define _HMForeach(MACRO, HMForeachN, ...) HMForeachN(MACRO, __VA_ARGS__)

#define _HMForeach1(MACRO, _0)\
    MACRO(0, _0)

#define _HMForeach2(MACRO, _0, _1) \
    _HMForeach1(MACRO, _0) \
    MACRO(1, _1)

#define _HMForeach3(MACRO, _0, _1, _2) \
    _HMForeach2(MACRO, _0, _1) \
    MACRO(2, _2)

#define _HMForeach4(MACRO, _0, _1, _2, _3) \
    _HMForeach3(MACRO, _0, _1, _2) \
    MACRO(3, _3)

#define _HMForeach5(MACRO, _0, _1, _2, _3, _4) \
    _HMForeach4(MACRO, _0, _1, _2, _3) \
    MACRO(4, _4)

#define _HMForeach6(MACRO, _0, _1, _2, _3, _4, _5) \
    _HMForeach5(MACRO, _0, _1, _2, _3, _4) \
    MACRO(5, _5)

#define _HMForeach7(MACRO, _0, _1, _2, _3, _4, _5, _6) \
    _HMForeach6(MACRO, _0, _1, _2, _3, _4, _5) \
    MACRO(6, _6)

#define _HMForeach8(MACRO, _0, _1, _2, _3, _4, _5, _6, _7) \
    _HMForeach7(MACRO, _0, _1, _2, _3, _4, _5, _6) \
    MACRO(7, _7)

#define _HMForeach9(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    _HMForeach8(MACRO, _0, _1, _2, _3, _4, _5, _6, _7) \
    MACRO(8, _8)

#define _HMForeach10(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    _HMForeach9(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8) \
    MACRO(9, _9)

#define _HMForeach11(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    _HMForeach10(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
    MACRO(10, _10)

#define _HMForeach12(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    _HMForeach11(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
    MACRO(11, _11)

#define _HMForeach13(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    _HMForeach12(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) \
    MACRO(12, _12)

#define _HMForeach14(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    _HMForeach13(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) \
    MACRO(13, _13)

#define _HMForeach15(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    _HMForeach14(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13) \
    MACRO(14, _14)

#define _HMForeach16(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    _HMForeach15(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14) \
    MACRO(15, _15)

#define _HMForeach17(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    _HMForeach16(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15) \
    MACRO(16, _16)

#define _HMForeach18(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    _HMForeach17(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16) \
    MACRO(17, _17)

#define _HMForeach19(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    _HMForeach18(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17) \
    MACRO(18, _18)

#define _HMForeach20(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19) \
    _HMForeach19(MACRO, _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18) \
    MACRO(19, _19)

#endif // HMLog_h
