#include "utility.hpp"
#include <string>

TEST_CASE("Stack copying")
{
	const std::string first{ "Very " };
	const std::string second{ "short!" };

	rapidstring s;
	rs_init(&s);
	rs_stack_cpy(&s, first.data());

	CMP_STR(&s, first);

	rs_stack_cpy(&s, second.data());

	CMP_STR(&s, second);

	rs_free(&s);
}

TEST_CASE("Heap copying")
{
	const std::string first{ "A very long string to get around SSO!" };
	const std::string second{ "Today is a fine day. Let's go." };

	rapidstring s;

	// Explicit capacity init required as heap_cpy doesn't allocate
	rs_init_w_cap(&s, first.length());
	rs_heap_cpy(&s, first.data());

	CMP_STR(&s, first);

	rs_reserve(&s, second.length());
	rs_heap_cpy(&s, second.data());

	CMP_STR(&s, second);

	rs_free(&s);
}

TEST_CASE("Stack and heap copying")
{
	const std::string first{ "Short!" };
	const std::string second{ "A very long string to get around SSO!" };

	rapidstring s;
	rs_init(&s);
	rs_cpy(&s, first.data());

	CMP_STR(&s, first);

	rs_cpy(&s, second.data());

	CMP_STR(&s, second);

	rs_free(&s);
}

TEST_CASE("Heap growth copying")
{
	const std::string first{ "A very long string to get around SSO!" };

	rapidstring s;
	rs_init_w_cap(&s, 1);

	rs_cpy(&s, first.data());

	CMP_STR(&s, first);

	rs_free(&s);
}

TEST_CASE("String copying")
{
	const std::string first{ "Visual Basic is the best language." };

	rapidstring s1;
	rs_init(&s1);

	rapidstring s2;
	rs_init_w(&s2, first.data());

	rs_cpy_rs(&s1, &s2);

	CMP_STR(&s1, first);

	rs_free(&s1);
	rs_free(&s2);
}