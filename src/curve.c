#include "curve.h"
#include <stdlib.h>

CurveZZ_p * buildCurveZZ_p(char * p, char * a, char * b, char * q, char * gx, char * gy, int base) {
    CurveZZ_p * curve = (CurveZZ_p *)malloc(sizeof(CurveZZ_p));
    mpz_init_set_str(curve->p, p, base);
    mpz_init_set_str(curve->a, a, base);
    mpz_init_set_str(curve->b, b, base);
    mpz_init_set_str(curve->q, q, base);
    curve->g = buildPointZZ_p(gx, gy, base);
    return curve;
}

void destroyCurveZZ_p(CurveZZ_p * curve) {
    mpz_clears(curve->p, curve->a, curve->b, curve->q, NULL);
    destroyPointZZ_p(curve->g);
    free(curve);
}

CurveZZ_pX * buildCurveZZ_pX(unsigned * pt, unsigned ptlen, unsigned degree, int a, char * q, char * gx, char * gy, int base) {
    CurveZZ_pX * curve = (CurveZZ_pX *)malloc(sizeof(CurveZZ_pX));
    curve->degree = degree;

    curve->pt = f2m_init(degree);
    curve->b = f2m_init(0);
    f2m_set_bit(curve->b, 0);  // Koblitz curve has b=1

    if(a == 1) {
        curve->a = f2m_init(0);
        f2m_set_bit(curve->a, 0);
    }
    else {
        curve->a = f2m_init(0);
    }

    unsigned i;
    for(i = 0; i < ptlen; i++) {
        f2m_set_bit(curve->pt, pt[i]);
    }

    mpz_init_set_str(curve->q, q, base);
    curve->g = buildPointZZ_pX(gx, gy, base, degree);

    return curve;
}

void destroyCurveZZ_pX(CurveZZ_pX * curve) {
    f2m_clear(curve->a);
    f2m_clear(curve->b);
    f2m_clear(curve->pt);
    mpz_clear(curve->q);
    destroyPointZZ_pX(curve->g);
    free(curve);
}

CurveZZ_p * buildP192() {
    return buildCurveZZ_p(
        "6277101735386680763835789423207666416083908700390324961279",
        "-3",
        "2455155546008943817740293915197451784769108058161191238065",
        "6277101735386680763835789423176059013767194773182842284081",
        "602046282375688656758213480587526111916698976636884684818",
        "174050332293622031404857552280219410364023488927386650641",
        10
    );
}

CurveZZ_p * buildP224() {
    return buildCurveZZ_p(
        "26959946667150639794667015087019630673557916260026308143510066298881",
        "-3",
        "18958286285566608000408668544493926415504680968679321075787234672564",
        "26959946667150639794667015087019625940457807714424391721682722368061",
        "19277929113566293071110308034699488026831934219452440156649784352033",
        "19926808758034470970197974370888749184205991990603949537637343198772",
        10
    );
}

CurveZZ_p * buildP256() {
    return buildCurveZZ_p(
        "115792089210356248762697446949407573530086143415290314195533631308867097853951",
        "-3",
        "41058363725152142129326129780047268409114441015993725554835256314039467401291",
        "115792089210356248762697446949407573529996955224135760342422259061068512044369",
        "48439561293906451759052585252797914202762949526041747995844080717082404635286",
        "36134250956749795798585127919587881956611106672985015071877198253568414405109",
        10
    );
}

CurveZZ_p * buildP384() {
    return buildCurveZZ_p(
        "39402006196394479212279040100143613805079739270465446667948293404245721771496870329047266088258938001861606973112319",
        "-3",
        "27580193559959705877849011840389048093056905856361568521428707301988689241309860865136260764883745107765439761230575",
        "39402006196394479212279040100143613805079739270465446667946905279627659399113263569398956308152294913554433653942643",
        "26247035095799689268623156744566981891852923491109213387815615900925518854738050089022388053975719786650872476732087",
        "8325710961489029985546751289520108179287853048861315594709205902480503199884419224438643760392947333078086511627871",
        10
    );
}

CurveZZ_p * buildP521() {
    return buildCurveZZ_p(
        "6864797660130609714981900799081393217269435300143305409394463459185543183397656052122559640661454554977296311391480858037121987999716643812574028291115057151",
        "-3",
        "1093849038073734274511112390766805569936207598951683748994586394495953116150735016013708737573759623248592132296706313309438452531591012912142327488478985984",
        "6864797660130609714981900799081393217269435300143305409394463459185543183397655394245057746333217197532963996371363321113864768612440380340372808892707005449",
        "2661740802050217063228768716723360960729859168756973147706671368418802944996427808491545080627771902352094241225065558662157113545570916814161637315895999846",
        "3757180025770020463545507224491183603594455134769762486694567779615544477440556316691234405012945539562144444537289428522585666729196580810124344277578376784",
        10
    );
}

CurveZZ_p * buildSecp256k1() {
    return buildCurveZZ_p(
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F",
        "0",
        "7",
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141",
        "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798",
        "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8",
        16
    );
}

CurveZZ_pX * buildK163() {
    unsigned coefficients[] = {163, 7, 6, 3, 0};
    return buildCurveZZ_pX(
        &coefficients[0],
        5,
        163,
        1,
        "4000000000000000000020108a2e0cc0d99f8a5ef",
        "2fe13c0537bbc11acaa07d793de4e6d5e5c94eee8",
        "289070fb05d38ff58321f2e800536d538ccdaa3d9",
        16
    );
}

CurveZZ_pX * buildK233() {
    unsigned coefficients[] = {233, 74, 0};
    return buildCurveZZ_pX(
        &coefficients[0],
        3,
        233,
        0,
        "8000000000000000000000000000069d5bb915bcd46efb1ad5f173abdf",
        "17232ba853a7e731af129f22ff4149563a419c26bf50a4c9d6eefad6126",
        "1db537dece819b7f70f555a67c427a8cd9bf18aeb9b56e0c11056fae6a3",
        16
    );
}

CurveZZ_pX * buildK283() {
    unsigned coefficients[] = {283, 12, 7, 5, 0};
    return buildCurveZZ_pX(
        &coefficients[0],
        5,
        283,
        0,
        "1ffffffffffffffffffffffffffffffffffe9ae2ed07577265dff7f94451e061e163c61",
        "503213f78ca44883f1a3b8162f188e553cd265f23c1567a16876913b0c2ac2458492836",
        "1ccda380f1c9e318d90f95d07e5426fe87e45c0e8184698e45962364e34116177dd2259",
        16
    );
}

CurveZZ_pX * buildK409() {
    unsigned coefficients[] = {409, 87, 0};
    return buildCurveZZ_pX(
        &coefficients[0],
        3,
        409,
        0,
        "7ffffffffffffffffffffffffffffffffffffffffffffffffffe5f83b2d4ea20400ec4557d5ed3e3e7ca5b4b5c83b8e01e5fcf",
        "060f05f658f49c1ad3ab1890f7184210efd0987e307c84c27accfb8f9f67cc2c460189eb5aaaa62ee222eb1b35540cfe9023746",
        "1e369050b7c4e42acba1dacbf04299c3460782f918ea427e6325165e9ea10e3da5f6c42e9c55215aa9ca27a5863ec48d8e0286b",
        16
    );
}

CurveZZ_pX * buildK571() {
    unsigned coefficients[] = {571, 10, 5, 2, 0};
    return buildCurveZZ_pX(
        &coefficients[0],
        5,
        571,
        0,
        "20000000000000000000000000000000000000000000000000000000000000000000000131850e1f19a63e4b391a8db917f4138b630d84be5d639381e91deb45cfe778f637c1001",
        "26eb7a859923fbc82189631f8103fe4ac9ca2970012d5d46024804801841ca44370958493b205e647da304db4ceb08cbbd1ba39494776fb988b47174dca88c7e2945283a01c8972",
        "349dc807f4fbf374f4aeade3bca95314dd58cec9f307a54ffc61efc006d8a2c9d4979c0ac44aea74fbebbb9f772aedcb620b01a7ba7af1b320430c8591984f601cd4c143ef1c7a3",
        16
    );
}
