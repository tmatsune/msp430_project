#ifndef ASSERT_H
#define ASSERT_H

void assert_handler(int condition, char *msg);
#define ASSERT(cond, msg) assert_handler(cond, msg)

#endif
