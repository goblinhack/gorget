//
// Copyright goblinhack@gmail.com
//

#include "my_dice_rolls.hpp"
#include "my_random.hpp"

[[nodiscard]] auto d10000() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 10000); }
[[nodiscard]] auto d1000() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 1000); }
[[nodiscard]] auto d100() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 100); }
[[nodiscard]] auto d10() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 10); }
[[nodiscard]] auto d11() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 11); }
[[nodiscard]] auto d12() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 12); }
[[nodiscard]] auto d13() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 13); }
[[nodiscard]] auto d14() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 14); }
[[nodiscard]] auto d15() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 15); }
[[nodiscard]] auto d16() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 16); }
[[nodiscard]] auto d17() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 17); }
[[nodiscard]] auto d18() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 18); }
[[nodiscard]] auto d19() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 19); }
[[nodiscard]] auto d20() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 20); }
[[nodiscard]] auto d2() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 2); }
[[nodiscard]] auto d3() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 3); }
[[nodiscard]] auto d4() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 4); }
[[nodiscard]] auto d50() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 50); }
[[nodiscard]] auto d5() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 5); }
[[nodiscard]] auto d6() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 6); }
[[nodiscard]] auto d7() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 7); }
[[nodiscard]] auto d8() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 8); }
[[nodiscard]] auto d9() -> int { return PCG_RANDOM_RANGE_INCLUSIVE(1, 9); }
