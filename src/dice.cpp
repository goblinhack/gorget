//
// Copyright goblinhack@gmail.com
//

#include "my_random.hpp"

auto d10000() -> int { return pcg_random_range_inclusive(1, 10000); }
auto d1000() -> int { return pcg_random_range_inclusive(1, 1000); }
auto d100() -> int { return pcg_random_range_inclusive(1, 100); }
auto d10() -> int { return pcg_random_range_inclusive(1, 10); }
auto d11() -> int { return pcg_random_range_inclusive(1, 11); }
auto d12() -> int { return pcg_random_range_inclusive(1, 12); }
auto d13() -> int { return pcg_random_range_inclusive(1, 13); }
auto d14() -> int { return pcg_random_range_inclusive(1, 14); }
auto d15() -> int { return pcg_random_range_inclusive(1, 15); }
auto d16() -> int { return pcg_random_range_inclusive(1, 16); }
auto d17() -> int { return pcg_random_range_inclusive(1, 17); }
auto d18() -> int { return pcg_random_range_inclusive(1, 18); }
auto d19() -> int { return pcg_random_range_inclusive(1, 19); }
auto d20() -> int { return pcg_random_range_inclusive(1, 20); }
auto d2() -> int { return pcg_random_range_inclusive(1, 2); }
auto d3() -> int { return pcg_random_range_inclusive(1, 3); }
auto d4() -> int { return pcg_random_range_inclusive(1, 4); }
auto d50() -> int { return pcg_random_range_inclusive(1, 50); }
auto d5() -> int { return pcg_random_range_inclusive(1, 5); }
auto d6() -> int { return pcg_random_range_inclusive(1, 6); }
auto d7() -> int { return pcg_random_range_inclusive(1, 7); }
auto d8() -> int { return pcg_random_range_inclusive(1, 8); }
auto d9() -> int { return pcg_random_range_inclusive(1, 9); }
