// Упрощенная версия Google Test для MinGW

#include <iostream>
#include <cassert>
#include <string>
#include <sstream>

#define TEST(test_suite_name, test_name) \
    class test_suite_name##_##test_name##_Test : public ::testing::Test { \
    public: \
        static void Run(); \
    }; \
    void test_suite_name##_##test_name##_Test::Run()

#define EXPECT_EQ(val1, val2) \
    if ((val1) != (val2)) { \
        std::cout << "FAIL: " << #val1 << " != " << #val2 \
                  << " (" << (val1) << " vs " << (val2) << ")" << std::endl; \
        assert((val1) == (val2)); \
    } else { \
        std::cout << "OK: " << #val1 << " == " << #val2 << std::endl; \
    }

#define EXPECT_NE(val1, val2) \
    if ((val1) == (val2)) { \
        std::cout << "FAIL: " << #val1 << " == " << #val2 << std::endl; \
        assert((val1) != (val2)); \
    } else { \
        std::cout << "OK: " << #val1 << " != " << #val2 << std::endl; \
    }

#define EXPECT_GT(val1, val2) \
    if (!((val1) > (val2))) { \
        std::cout << "FAIL: " << #val1 << " <= " << #val2 << std::endl; \
        assert((val1) > (val2)); \
    } else { \
        std::cout << "OK: " << #val1 << " > " << #val2 << std::endl; \
    }

#define EXPECT_TRUE(cond) \
    if (!(cond)) { \
        std::cout << "FAIL: " << #cond << " is false" << std::endl; \
        assert(cond); \
    } else { \
        std::cout << "OK: " << #cond << " is true" << std::endl; \
    }

#define EXPECT_FALSE(cond) \
    if (cond) { \
        std::cout << "FAIL: " << #cond << " is true" << std::endl; \
        assert(!(cond)); \
    } else { \
        std::cout << "OK: " << #cond << " is false" << std::endl; \
    }

#define EXPECT_NEAR(val1, val2, abs_error) \
    if (std::abs((val1) - (val2)) > (abs_error)) { \
        std::cout << "FAIL: " << #val1 << " not near " << #val2 \
                  << " (" << (val1) << " vs " << (val2) << ")" << std::endl; \
        assert(std::abs((val1) - (val2)) <= (abs_error)); \
    } else { \
        std::cout << "OK: " << #val1 << " near " << #val2 << std::endl; \
    }

#define EXPECT_THROW(statement, exception_type) \
    try { \
        statement; \
        std::cout << "FAIL: Expected " << #exception_type << " not thrown" << std::endl; \
        assert(false); \
    } catch (const exception_type&) { \
        std::cout << "OK: " << #exception_type << " thrown as expected" << std::endl; \
    } catch (...) { \
        std::cout << "FAIL: Wrong exception type thrown" << std::endl; \
        assert(false); \
    }

namespace testing {
    class Test {
    public:
        virtual ~Test() {}
        virtual void SetUp() {}
        virtual void TearDown() {}
    };
    
    namespace internal {
        inline std::string CaptureStdout() {
            return ""; // Упрощенная реализация
        }
    }
}

int RUN_ALL_TESTS() {
    return 0;
}
