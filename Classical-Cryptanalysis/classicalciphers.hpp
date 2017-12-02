#ifndef __CLASSICALCIPHERS_HPP
#define __CLASSICALCIPHERS_HPP

using namespace __shedskin__;
namespace __classicalciphers__ {

extern str *const_0, *const_1, *const_10, *const_11, *const_12, *const_13, *const_14, *const_15, *const_16, *const_17, *const_18, *const_19, *const_2, *const_20, *const_21, *const_22, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;

class Caesar;
class Vigenere;
class Substitution;
class Affine;
class ColumnarTransposition;
class Playfair;
class PolybiusSquare;
class Adfgx;

typedef __ss_int (*lambda4)(str *);
typedef __ss_int (*lambda2)(str *);
typedef str *(*lambda3)(tuple2<__ss_int, str *> *);
typedef __ss_int (*lambda1)(str *);
typedef str *(*lambda0)(str *, __ss_int);

extern __ss_int k;
extern str *ALPHABET, *__name__, *c, *d, *key, *key1, *key2, *test;
;

extern class_ *cl_Caesar;
class Caesar : public pyobj {
public:

    Caesar() { this->__class__ = cl_Caesar; }
    static str *encrypt(str *message, __ss_int key);
    static str *decrypt(str *ciphertext, __ss_int key);
};

extern class_ *cl_Vigenere;
class Vigenere : public pyobj {
public:

    Vigenere() { this->__class__ = cl_Vigenere; }
    static str *encrypt(str *message, str *key);
    static str *decrypt(str *ciphertext, str *key);
};

extern class_ *cl_Substitution;
class Substitution : public pyobj {
public:

    Substitution() { this->__class__ = cl_Substitution; }
    static str *encrypt(str *message, str *key);
    static str *decrypt(str *ciphertex, str *key);
    static str *buildAlphabet(str *key);
};

extern class_ *cl_Affine;
class Affine : public pyobj {
public:

    Affine() { this->__class__ = cl_Affine; }
    static str *encrypt(str *message, tuple2<__ss_int, __ss_int> *key);
    static __ss_int modReverse(__ss_int a, __ss_int b);
    static str *decrypt(str *ciphertext, tuple2<__ss_int, __ss_int> *key);
};

extern class_ *cl_ColumnarTransposition;
class ColumnarTransposition : public pyobj {
public:

    ColumnarTransposition() { this->__class__ = cl_ColumnarTransposition; }
    static str *encrypt(str *message, str *key);
    static list<__ss_int> *transformkey(str *key);
    static str *decrypt(str *ciphertext, str *key);
};

extern class_ *cl_Playfair;
class Playfair : public pyobj {
public:

    Playfair() { this->__class__ = cl_Playfair; }
    static void *encrypt(str *message, str *key);
    static str *buildtable(str *key);
    static void *decrypt(str *message, str *key);
};

extern class_ *cl_PolybiusSquare;
class PolybiusSquare : public pyobj {
public:

    PolybiusSquare() { this->__class__ = cl_PolybiusSquare; }
    static str *encrypt(str *message, pyseq<str *> *key, str *letters);
    static str *decrypt(str *ciphertext, pyseq<str *> *key, str *letters);
    static str *generatekey();
};

extern class_ *cl_Adfgx;
class Adfgx : public pyobj {
public:

    Adfgx() { this->__class__ = cl_Adfgx; }
    static str *encrypt(str *message, str *key1, str *key2);
    static str *decrypt(str *ciphertext, str *key1, str *key2);
};

str *offset(str *__ss_char, __ss_int offset);

} // module namespace
#endif
