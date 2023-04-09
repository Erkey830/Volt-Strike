#include "global.h"
#include "test.h"
#include "random.h"

TEST("RandomUniform generates lo..hi")
{
    u32 lo, hi, i;
    PARAMETRIZE { lo = 0; hi = 1; }
    PARAMETRIZE { lo = 0; hi = 2; }
    PARAMETRIZE { lo = 0; hi = 3; }
    PARAMETRIZE { lo = 2; hi = 4; }
    for (i = 0; i < 1024; i++)
    {
        u32 r = RandomUniformDefault(RNG_NONE, lo, hi);
        EXPECT(lo <= r && r <= hi);
    }
}

TEST("RandomWeighted generates 0..n-1")
{
    u32 n, sum, i;
    static const u8 ws[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    PARAMETRIZE { n = 1; }
    PARAMETRIZE { n = 2; }
    PARAMETRIZE { n = 3; }
    PARAMETRIZE { n = 4; }
    ASSUME(n <= ARRAY_COUNT(ws));
    for (i = 0, sum = 0; i < n; i++)
        sum += ws[i];
    for (i = 0; i < 1024; i++)
    {
        u32 r = RandomWeightedArrayDefault(RNG_NONE, sum, n, ws);
        EXPECT(0 <= r && r < n);
    }
}

TEST("RandomUniform generates uniform distribution")
{
    u32 i, error;
    u16 distribution[4];

    memset(distribution, 0, sizeof(distribution));
    for (i = 0; i < 4096; i++)
    {
        u32 r = RandomUniformDefault(RNG_NONE, 0, ARRAY_COUNT(distribution));
        EXPECT(0 <= r && r < ARRAY_COUNT(distribution));
        distribution[r]++;
    }

    error = 0;
    for (i = 0; i < ARRAY_COUNT(distribution); i++)
        error += abs(UQ_4_12(0.25) - distribution[i]);

    EXPECT_LT(error, UQ_4_12(0.025));
}

TEST("RandomWeighted generates distribution in proportion to the weights")
{
    u32 i, sum, error;
    static const u8 ws[4] = { 1, 2, 2, 3 };
    u16 distribution[ARRAY_COUNT(ws)];

    for (i = 0, sum = 0; i < ARRAY_COUNT(ws); i++)
        sum += ws[i];

    memset(distribution, 0, sizeof(distribution));
    for (i = 0; i < 4096; i++)
    {
        u32 r = RandomWeightedArrayDefault(RNG_NONE, sum, ARRAY_COUNT(ws), ws);
        EXPECT(0 <= r && r < ARRAY_COUNT(ws));
        distribution[r]++;
    }

    error = 0;
    error += abs(UQ_4_12(0.125) - distribution[0]);
    error += abs(UQ_4_12(0.250) - distribution[1]);
    error += abs(UQ_4_12(0.250) - distribution[2]);
    error += abs(UQ_4_12(0.375) - distribution[3]);

    EXPECT_LT(error, UQ_4_12(0.025));
}
