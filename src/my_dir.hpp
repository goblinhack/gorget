//
// Copyright goblinhack@gmail.com
//

#ifndef MY_FILENODE_HPP_
#define MY_FILENODE_HPP_

auto dir_exists(const char *filename) -> bool;
auto dir_dot() -> char *;
auto dir_dotdot(char *in) -> char *;
auto dospath2unix(char *in) -> char *;

#endif
