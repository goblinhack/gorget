//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_FILENODE_HPP_
#define _MY_FILENODE_HPP_

bool  dir_exists(const char *filename);
char *dir_dot(void);
char *dir_dotdot(char *in);
char *dospath2unix(char *in);

#endif
