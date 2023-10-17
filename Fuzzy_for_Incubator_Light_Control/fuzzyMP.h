// FUNGSI Keanggotaan Error
float error_MN(float x)
{
    if (x > -1)
        return 0;
    else if (x <= -1 && x > -5)
        return ((-1 - x) / 4);
    else
        return 1;
}

float error_N(float x)
{
    if (x <= -5 || x > 0)
        return 0;
    else if (x > -5 && x <= -1)
        return ((x - (-5)) / 4);
    else if (x > -1 && x <= 0)
        return ((0 - x) / 1);

    return 0;
}

float error_Z(float x)
{
    if (x <= -1 || x > 1)
        return 0;
    else if (x > -1 && x <= 0)
        return ((x - (-1)) / 1);
    else if (x > 0 && x <= 1)
        return ((1 - x) / 1);

    return 0;
}

float error_P(float x)
{
    if (x <= 0 || x > 5)
        return 0;
    else if (x > 0 && x <= 1)
        return (x - 0 / 1);
    else if (x > 1 && x <= 5)
        return ((5 - x) / 4);

    return 0;
}

float error_MP(float x)
{
    if (x < 1)
        return 0;
    else if (x >= 1 && x < 5)
        return float(((x - 1) / 4));
    else
        return 1;
}

// Fungsi Keanggotaan Delta Error

float deltaError_DN(float x)
{
    if (x >= 0.5)
        return 0;
    else if (x >= 0.3 && x < 0.5)
        return (((0.5 - x)) / 0.2);
    else
        return 1;
}

float deltaError_Z(float x)
{
    if (x <= 0.3 || x > 0.7)
        return 0;
    else if (x > 0.3 && x <= 0.5)
        return ((x - 0.3) / 0.2);
    else if (x > 0.5 && x <= 0.7)
        return ((0.7 - x) / 0.2);
    return 0;
}

float deltaError_DP(float x)
{
    if (x < 0.5)
        return 0;
    else if (x >= 0.5 && x < 0.7)
        return ((x - 0.5) / 0.2);
    else
        return 1;
}