#include "builtin.hpp"
#include "time.hpp"
#include "string.hpp"
#include "math.hpp"
#include "random.hpp"
#include "classicalciphers.hpp"

namespace __classicalciphers__ {

str *const_0, *const_1, *const_10, *const_11, *const_12, *const_13, *const_14, *const_15, *const_16, *const_17, *const_18, *const_19, *const_2, *const_20, *const_21, *const_22, *const_3, *const_4, *const_5, *const_6, *const_7, *const_8, *const_9;


str *ALPHABET, *__name__, *c, *d, *key, *key1, *key2, *test;
__ss_int k;
;

class list_comp_0 : public __iter<str *> {
public:
    str *__8, *ch;
    __ss_int __10;
    __iter<str *> *__9;
    str::for_in_loop __11;

    str *message;
    str *cipher_alph;
    int __last_yield;

    list_comp_0(str *message, str *cipher_alph);
    str * __get_next();
};

static inline list<str *> *list_comp_1(str *offseted_alph, str *key);
class list_comp_2 : public __iter<str *> {
public:
    str *__16, *ch;
    __ss_int __18;
    __iter<str *> *__17;
    str::for_in_loop __19;

    str *cipher_alph;
    str *ciphertex;
    int __last_yield;

    list_comp_2(str *cipher_alph, str *ciphertex);
    str * __get_next();
};

class list_comp_3 : public __iter<str *> {
public:
    str *__23, *ch;
    __ss_int __25;
    __iter<str *> *__24;
    str::for_in_loop __26;

    str *message;
    tuple2<__ss_int, __ss_int> *key;
    int __last_yield;

    list_comp_3(str *message, tuple2<__ss_int, __ss_int> *key);
    str * __get_next();
};

class list_comp_4 : public __iter<str *> {
public:
    __iter<str *> *__28;
    __ss_int __29;
    str *__27, *ch;
    str::for_in_loop __30;

    str *ciphertext;
    tuple2<__ss_int, __ss_int> *key;
    int __last_yield;

    list_comp_4(str *ciphertext, tuple2<__ss_int, __ss_int> *key);
    str * __get_next();
};

static inline list<str *> *list_comp_5(str *message, str *key);
static inline list<str *> *list_comp_6(str *ciphertext, str *key);
static inline list<tuple2<__ss_int, str *> *> *list_comp_7(str *key);
static inline list<__ss_int> *list_comp_8(str *key);
static inline list<str *> *list_comp_9(str *key);
static inline list<str *> *list_comp_11(str *message, str *letters, pyseq<str *> *key);
static inline list<str *> *list_comp_12(str *ciphertext);
static inline list<str *> *list_comp_13(str *letters, list<str *> *c_list, pyseq<str *> *key);
static inline __ss_int __lambda4__(str *x);
static inline __ss_int __lambda2__(str *x);
static inline str *__lambda3__(tuple2<__ss_int, str *> *x);
static inline __ss_int __lambda1__(str *x);

list_comp_0::list_comp_0(str *message, str *cipher_alph) {
    this->message = message;
    this->cipher_alph = cipher_alph;
    __last_yield = -1;
}

str * list_comp_0::__get_next() {
    if(!__last_yield) goto __after_yield_0;
    __last_yield = 0;

    FOR_IN(ch,message,8,10,11)
        __result = cipher_alph->__getfast__(ALPHABET->index(ch->upper()));
        return __result;
        __after_yield_0:;
    END_FOR

    __stop_iteration = true;
}

static inline list<str *> *list_comp_1(str *offseted_alph, str *key) {
    __iter<str *> *__13;
    __ss_int __14;
    str *__12, *ch;
    str::for_in_loop __15;

    list<str *> *__ss_result = new list<str *>();

    FOR_IN(ch,offseted_alph,12,14,15)
        if (__NOT((key->upper())->__contains__(ch))) {
            __ss_result->append(ch);
        }
    END_FOR

    return __ss_result;
}

list_comp_2::list_comp_2(str *cipher_alph, str *ciphertex) {
    this->cipher_alph = cipher_alph;
    this->ciphertex = ciphertex;
    __last_yield = -1;
}

str * list_comp_2::__get_next() {
    if(!__last_yield) goto __after_yield_0;
    __last_yield = 0;

    FOR_IN(ch,ciphertex,16,18,19)
        __result = ALPHABET->__getfast__(cipher_alph->index(ch->upper()));
        return __result;
        __after_yield_0:;
    END_FOR

    __stop_iteration = true;
}

list_comp_3::list_comp_3(str *message, tuple2<__ss_int, __ss_int> *key) {
    this->message = message;
    this->key = key;
    __last_yield = -1;
}

str * list_comp_3::__get_next() {
    if(!__last_yield) goto __after_yield_0;
    __last_yield = 0;

    FOR_IN(ch,message,23,25,26)
        __result = ALPHABET->__getfast__(__mods(((ALPHABET->index(ch)*key->__getfirst__())+key->__getsecond__()), 26));
        return __result;
        __after_yield_0:;
    END_FOR

    __stop_iteration = true;
}

list_comp_4::list_comp_4(str *ciphertext, tuple2<__ss_int, __ss_int> *key) {
    this->ciphertext = ciphertext;
    this->key = key;
    __last_yield = -1;
}

str * list_comp_4::__get_next() {
    if(!__last_yield) goto __after_yield_0;
    __last_yield = 0;

    FOR_IN(ch,ciphertext,27,29,30)
        __result = ALPHABET->__getfast__(__mods((Affine::modReverse(key->__getfirst__(), 26)*(ALPHABET->index(ch)-key->__getsecond__())), 26));
        return __result;
        __after_yield_0:;
    END_FOR

    __stop_iteration = true;
}

static inline list<str *> *list_comp_5(str *message, str *key) {
    __iter<__ss_int> *__33;
    list<__ss_int> *__32;
    __ss_int __34, __36, __37, i, k;
    list<__ss_int>::for_in_loop __35;

    list<str *> *__ss_result = new list<str *>();

    __32 = ColumnarTransposition::transformkey(key);
    FOR_IN(i,__32,32,34,35)
        FAST_FOR(k,0,len(message),1,36,37)
            if ((__mods(k, len(key))==i)) {
                __ss_result->append(message->__getfast__(k));
            }
        END_FOR

    END_FOR

    return __ss_result;
}

static inline list<str *> *list_comp_6(str *ciphertext, str *key) {
    __ss_int __38, __39, __40, __41, i, k;

    list<str *> *__ss_result = new list<str *>();

    FAST_FOR(k,0,__floordiv(len(ciphertext),len(key)),1,38,39)
        FAST_FOR(i,0,len(key),1,40,41)
            __ss_result->append(ciphertext->__getfast__((__floordiv(((ColumnarTransposition::transformkey(key))->index(i)*len(ciphertext)),len(key))+k)));
        END_FOR

    END_FOR

    return __ss_result;
}

static inline list<tuple2<__ss_int, str *> *> *list_comp_7(str *key) {
    __ss_int __44;
    __iter<tuple2<__ss_int, str *> *>::for_in_loop __45;
    __iter<tuple2<__ss_int, str *> *> *__42, *__43;
    tuple2<__ss_int, str *> *i;

    list<tuple2<__ss_int, str *> *> *__ss_result = new list<tuple2<__ss_int, str *> *>();

    __42 = enumerate(key);
    FOR_IN(i,__42,42,44,45)
        __ss_result->append(i);
    END_FOR

    return __ss_result;
}

static inline list<__ss_int> *list_comp_8(str *key) {
    list<tuple2<__ss_int, str *> *> *__46;
    __ss_int __48;
    list<tuple2<__ss_int, str *> *>::for_in_loop __49;
    __iter<tuple2<__ss_int, str *> *> *__47;
    tuple2<__ss_int, str *> *i;

    list<__ss_int> *__ss_result = new list<__ss_int>();

    __46 = sorted(list_comp_7(key), 0, __lambda3__, 0);
    __ss_result->resize(len(__46));
    FOR_IN(i,__46,46,48,49)
        __ss_result->units[__48] = i->__getfirst__();
    END_FOR

    return __ss_result;
}

static inline list<str *> *list_comp_9(str *key) {
    __ss_int __52;
    str *__50, *ch;
    __ss_bool __54, __55;
    __iter<str *> *__51;
    str::for_in_loop __53;

    list<str *> *__ss_result = new list<str *>();

    FOR_IN(ch,ALPHABET,50,52,53)
        if ((__NOT(key->__contains__(ch)) and __ne(ch, const_0))) {
            __ss_result->append(ch);
        }
    END_FOR

    return __ss_result;
}

static inline list<str *> *list_comp_11(str *message, str *letters, pyseq<str *> *key) {
    str *__58, *ch;
    __ss_int __60;
    __iter<str *> *__59;
    str::for_in_loop __61;

    list<str *> *__ss_result = new list<str *>();

    __ss_result->resize(len(message));
    FOR_IN(ch,message,58,60,61)
        __ss_result->units[__60] = (letters->__getfast__(__floordiv(key->index(ch),5)))->__add__(letters->__getfast__(__mods(key->index(ch), 5)));
    END_FOR

    return __ss_result;
}

static inline list<str *> *list_comp_12(str *ciphertext) {
    __ss_int __62, __63, i;

    list<str *> *__ss_result = new list<str *>();

    FAST_FOR(i,1,len(ciphertext),2,62,63)
        __ss_result->append((ciphertext->__getfast__((i-1)))->__add__(ciphertext->__getfast__(i)));
    END_FOR

    return __ss_result;
}

static inline list<str *> *list_comp_13(str *letters, list<str *> *c_list, pyseq<str *> *key) {
    list<str *> *__64;
    list<str *>::for_in_loop __67;
    __iter<str *> *__65;
    __ss_int __66;
    str *ch;

    list<str *> *__ss_result = new list<str *>();

    __ss_result->resize(len(c_list));
    FOR_IN(ch,c_list,64,66,67)
        __ss_result->units[__66] = key->__getitem__(((letters->index(ch->__getfast__(0))*5)+letters->index(ch->__getfast__(1))));
    END_FOR

    return __ss_result;
}

static inline __ss_int __lambda4__(str *x) {
    
    return key->index(x);
}

static inline __ss_int __lambda2__(str *x) {
    
    return (26-ALPHABET->index(x));
}

static inline str *__lambda3__(tuple2<__ss_int, str *> *x) {
    
    return x->__getsecond__();
}

static inline __ss_int __lambda1__(str *x) {
    
    return ALPHABET->index(x);
}

str *offset(str *__ss_char, __ss_int offset) {
    
    return ALPHABET->__getfast__(__mods((ALPHABET->index(__ss_char)+offset), 26));
}

/**
class Caesar
*/

class_ *cl_Caesar;

str *Caesar::encrypt(str *message, __ss_int key) {
    
    return (const_1)->join(map(2, offset, (new list<str *>(message)), ((new list<__ss_int>(1,key)))->__mul__(len(message))));
}

str *Caesar::decrypt(str *ciphertext, __ss_int key) {
    
    return (const_1)->join(map(2, offset, (new list<str *>(ciphertext)), ((new list<__ss_int>(1,(26-key))))->__mul__(len(ciphertext))));
}


/**
class Vigenere
*/

class_ *cl_Vigenere;

str *Vigenere::encrypt(str *message, str *key) {
    
    return (const_1)->join(map(2, offset, message, ((new list<__ss_int>(map(1, __lambda1__, key))))->__mul__((__floordiv(len(message),len(key))+1))));
}

str *Vigenere::decrypt(str *ciphertext, str *key) {
    
    return (const_1)->join(map(2, offset, ciphertext, ((new list<__ss_int>(map(1, __lambda2__, key))))->__mul__((__floordiv(len(ciphertext),len(key))+1))));
}


/**
class Substitution
*/

class_ *cl_Substitution;

str *Substitution::encrypt(str *message, str *key) {
    str *cipher_alph;

    cipher_alph = Substitution::buildAlphabet(key);
    return (const_1)->join(new list_comp_0(message, cipher_alph));
}

str *Substitution::decrypt(str *ciphertex, str *key) {
    str *cipher_alph;

    cipher_alph = Substitution::buildAlphabet(key);
    return (const_1)->join(new list_comp_2(cipher_alph, ciphertex));
}

str *Substitution::buildAlphabet(str *key) {
    str *offseted_alph;

    offseted_alph = (const_1)->join(map(2, offset, (new list<str *>(ALPHABET)), ((new list<__ss_int>(1,(ALPHABET->index((key->upper())->__getfast__((-1)))+1))))->__mul__(len(ALPHABET))));
    return (key->upper())->__add__((const_1)->join(list_comp_1(offseted_alph, key)));
}


/**
class Affine
*/

class_ *cl_Affine;

str *Affine::encrypt(str *message, tuple2<__ss_int, __ss_int> *key) {
    
    return (const_1)->join(new list_comp_3(message, key));
}

__ss_int Affine::modReverse(__ss_int a, __ss_int b) {
    list<__ss_int> *__20, *__21, *__22, *r, *s, *t;
    __ss_int q;

    __20 = (new list<__ss_int>(2,___min(2, 0, a, b),___max(2, 0, a, b)));
    __21 = (new list<__ss_int>(2,1,0));
    __22 = (new list<__ss_int>(2,0,1));
    r = __20;
    s = __21;
    t = __22;

    while ((r->__getfast__((-1))!=1)) {
        q = __floordiv(r->__getfast__((-2)),r->__getfast__((-1)));
        r->append((r->__getfast__((-2))-(q*r->__getfast__((-1)))));
        s->append((s->__getfast__((-2))-(q*s->__getfast__((-1)))));
        t->append((t->__getfast__((-2))-(q*t->__getfast__((-1)))));
    }
    return __mods(s->__getfast__((-1)), r->__getfast__(1));
}

str *Affine::decrypt(str *ciphertext, tuple2<__ss_int, __ss_int> *key) {
    
    try {
        return (const_1)->join(new list_comp_4(ciphertext, key));
    } catch (ZeroDivisionError *) {
    }
    return 0;
}


/**
class ColumnarTransposition
*/

class_ *cl_ColumnarTransposition;

str *ColumnarTransposition::encrypt(str *message, str *key) {
    str *res;

    message = message->__add__((const_2)->__mul__(__mods((0-__mods(len(message), len(key))), len(key))));
    res = (const_1)->join(list_comp_5(message, key));
    return res;
}

list<__ss_int> *ColumnarTransposition::transformkey(str *key) {
    
    return list_comp_8(key);
}

str *ColumnarTransposition::decrypt(str *ciphertext, str *key) {
    
    return (const_1)->join(list_comp_6(ciphertext, key));
}


/**
class Playfair
*/

class_ *cl_Playfair;

void *Playfair::encrypt(str *message, str *key) {
    
    return Playfair::substitution();
}

str *Playfair::buildtable(str *key) {
    
    return ((const_1)->join(sorted((new set<str *>(key)), 0, __lambda4__, 0)))->__add__((const_1)->join(list_comp_9(key)));
}

void *Playfair::decrypt(str *message, str *key) {
    
    return Playfair::substitution();
}


/**
class PolybiusSquare
*/

class_ *cl_PolybiusSquare;

str *PolybiusSquare::encrypt(str *message, pyseq<str *> *key, str *letters) {
    
    return (const_1)->join(list_comp_11(message, letters, key));
}

str *PolybiusSquare::decrypt(str *ciphertext, pyseq<str *> *key, str *letters) {
    list<str *> *c_list;

    c_list = list_comp_12(ciphertext);
    return (const_1)->join(list_comp_13(letters, c_list, key));
}

str *PolybiusSquare::generatekey() {
    list<str *> *l;
    str *alph;

    alph = ALPHABET->replace(const_0, const_1);
    l = (new list<str *>(alph));
    __random__::shuffle(l);
    return (const_1)->join(l);
}


/**
class Adfgx
*/

class_ *cl_Adfgx;

str *Adfgx::encrypt(str *message, str *key1, str *key2) {
    str *stage1, *stage2;

    stage1 = PolybiusSquare::encrypt(message, key1, const_3);
    stage2 = ColumnarTransposition::encrypt(stage1, key2);
    return stage2;
}

str *Adfgx::decrypt(str *ciphertext, str *key1, str *key2) {
    str *stage1, *stage2;

    stage1 = ColumnarTransposition::decrypt(ciphertext, key2);
    stage2 = PolybiusSquare::decrypt(stage1, key1, const_3);
    return stage2;
}


void __init() {
    const_0 = __char_cache[74];;
    const_1 = new str("");
    const_2 = __char_cache[88];;
    const_3 = new str("ADFGX");
    const_4 = new str("__main__");
    const_5 = new str("---Caesar---");
    const_6 = new str("DEFENDTHEEASTWALLOFTHECASTLE");
    const_7 = new str("---Vigenere---");
    const_8 = new str("FORTIFICATION");
    const_9 = new str("---Substitution---");
    const_10 = new str("zebra");
    const_11 = new str("---Affine---");
    const_12 = new str("---Atbash---");
    const_13 = new str("---Columnar Transposition---");
    const_14 = new str("GERMAN");
    const_15 = new str("---Playfair Cipher---");
    const_16 = new str("monarchy");
    const_17 = new str("wearediscoveredsaveyourselfx");
    const_18 = new str("---Polybius Square Cipher---");
    const_19 = new str("ABCDE");
    const_20 = new str("---ADFGX Cipher---");
    const_21 = new str("phqgmeaynofdxkrcvszwbutil");
    const_22 = new str("ATTACK");

    __name__ = new str("__main__");

    ALPHABET = __string__::ascii_uppercase;
    cl_Caesar = new class_("Caesar", 5, 5);
    cl_Vigenere = new class_("Vigenere", 4, 4);
    cl_Substitution = new class_("Substitution", 51, 51);
    cl_Affine = new class_("Affine", 49, 49);
    cl_ColumnarTransposition = new class_("ColumnarTransposition", 53, 53);
    cl_Playfair = new class_("Playfair", 54, 54);
    cl_PolybiusSquare = new class_("PolybiusSquare", 1, 1);
    cl_Adfgx = new class_("Adfgx", 50, 50);
    if (__eq(__name__, const_4)) {
        print2(NULL,0,1, const_5);
        test = const_6;
        k = 1;
        c = Caesar::encrypt(test, k);
        d = Caesar::decrypt(c, k);
        print2(NULL,0,1, c);
        print2(NULL,0,1, d);
        print2(NULL,0,1, const_7);
        test = const_6;
        c = Vigenere::encrypt(test, (const_8)->upper());
        d = Vigenere::decrypt(c, (const_8)->upper());
        print2(NULL,0,1, c);
        print2(NULL,0,1, d);
        print2(NULL,0,1, const_9);
        test = const_6;
        c = Substitution::encrypt(test, const_10);
        print2(NULL,0,1, c);
        d = Substitution::decrypt(c, const_10);
        print2(NULL,0,1, d);
        print2(NULL,0,1, const_11);
        test = const_6;
        c = Affine::encrypt(test, (new tuple2<__ss_int, __ss_int>(2,5,7)));
        print2(NULL,0,1, c);
        d = Affine::decrypt(c, (new tuple2<__ss_int, __ss_int>(2,5,7)));
        print2(NULL,0,1, d);
        print2(NULL,0,1, const_12);
        test = ALPHABET;
        c = Affine::encrypt(test, (new tuple2<__ss_int, __ss_int>(2,25,25)));
        print2(NULL,0,1, c);
        d = Affine::decrypt(c, (new tuple2<__ss_int, __ss_int>(2,25,25)));
        print2(NULL,0,1, d);
        print2(NULL,0,1, const_13);
        test = (const_6)->upper();
        c = ColumnarTransposition::encrypt(test, const_14);
        print2(NULL,0,1, c);
        d = ColumnarTransposition::decrypt(c, const_14);
        print2(NULL,0,1, d);
        print2(NULL,0,1, const_15);
        key = Playfair::buildtable((const_16)->upper());
        c = ((str *)(Playfair::encrypt((const_17)->upper(), key)));
        print2(NULL,0,1, c);
        d = ((str *)(Playfair::decrypt(c, key)));
        print2(NULL,0,1, d);
        print2(NULL,0,1, const_18);
        key = PolybiusSquare::generatekey();
        test = const_6;
        c = PolybiusSquare::encrypt(test->upper(), (new list<str *>(key)), const_19);
        print2(NULL,0,1, c);
        d = PolybiusSquare::decrypt(c, (new list<str *>(key)), const_19);
        print2(NULL,0,1, d);
        print2(NULL,0,1, const_20);
        key1 = (const_21)->upper();
        key2 = const_14;
        test = const_22;
        c = Adfgx::encrypt(test, key1, key2);
        print2(NULL,0,1, c);
        d = Adfgx::decrypt(c, key1, key2);
        print2(NULL,0,1, d);
    }
}

} // module namespace

int main(int __ss_argc, char **__ss_argv) {
    __shedskin__::__init();
    __string__::__init();
    __math__::__init();
    __time__::__init();
    __random__::__init();
    __shedskin__::__start(__classicalciphers__::__init);
}
