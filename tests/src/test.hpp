#define ASSERT(msg, stmt) if(!(stmt)) throw std::invalid_argument(msg)
#define ASSERT_EQUALS(msg, val, target) ASSERT(msg, val == target)
#define ASSERT_TRUE(msg, val) ASSERT_EQUALS(msg, val, true)
#define ASSERT_FALSE(msg, val) ASSERT_EQUALS(msg, val, false)

#define DEBUG(msg, ...) std::cout << msg << ": "; __VA_ARGS__; std::cout << "\n"
#define LOG(obj) std::cout << (obj)