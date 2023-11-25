// FUNGSI Keanggotaan Error
float error_MN(float x)
{
    if (x > -12)
        return 0;
    else if (x <= -12 && x > -25)
        return ((-12 - x) / 13);
    else
        return 1;
}

float error_N(float x)
{
    if (x <= -14 || x > -2)
        return 0;
    else if (x > -14 && x <= -8)
        return ((x - (-14)) / 6);
    else if (x > -8 && x <= -2)
        return (((-2) - x) / 1);

    return 0;
}

float error_Z(float x)
{
    if (x <= -3 || x > 3)
        return 0;
    else if (x > -3 && x <= 0)
        return ((x - (-3)) / 3);
    else if (x > 0 && x <= 3)
        return ((3 - x) / 3);

    return 0;
}

float error_P(float x)
{
    if (x <= 2 || x > 14)
        return 0;
    else if (x > 2 && x <= 8)
        return ((x - 2) / 6);
    else if (x > 8 && x <= 14)
        return ((8 - x) / 6);

    return 0;
}

float error_MP(float x)
{
    if (x < 12)
        return 0;
    else if (x >= 12 && x < 25)
        return float(((x - 12) / 13));
    else
        return 1;
}

// Fungsi Keanggotaan Delta Error

float deltaError_DN(float x)
{
    if (x >= 2)
        return 0;
    else if (x >= 0 && x < 2)
        return (((2 - x)) / 2);
    else
        return 1;
}

float deltaError_DS(float x)
{
    if (x <= 1 || x > 11)
        return 0;
    else if (x > 1 && x <= 6)
        return ((x - 1) / 5);
    else if (x > 6 && x <= 11)
        return ((11 - x) / 5);
    return 0;
}

float deltaError_DM(float x)
{
    if (x <= 10 || x > 25)
        return 0;
    else if (x > 10 && x <= 15)
        return ((x - 10) / 5);
    else if (x > 15 && x <= 25)
        return ((25 - x) / 10);
    return 0;
}

float deltaError_DP(float x)
{
    if (x < 22)
        return 0;
    else if (x >= 22 && x < 40)
        return ((x - 22) / 18);
    else
        return 1;
}