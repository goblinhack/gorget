//
// Copyright goblinhack@gmail.com
//

#include "my_random.hpp"

auto d10000() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 10000); }
auto d1000() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 1000); }
auto d100() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 100); }
auto d10() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 10); }
auto d11() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 11); }
auto d12() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 12); }
auto d13() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 13); }
auto d14() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 14); }
auto d15() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 15); }
auto d16() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 16); }
auto d17() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 17); }
auto d18() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 18); }
auto d19() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 19); }
auto d20() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 20); }
auto d2() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 2); }
auto d3() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 3); }
auto d4() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 4); }
auto d50() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 50); }
auto d5() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 5); }
auto d6() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 6); }
auto d7() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 7); }
auto d8() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 8); }
auto d9() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 9); }
