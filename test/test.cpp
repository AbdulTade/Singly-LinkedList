# define CATCH_CONFIG_MAIN

# include "../headers/catch.hpp"
# include "../headers/linkedlist.hpp"

LinkedList<int> ll{};

TEST_CASE("check if element length is zero for empty list","[LinkedList<int>::length()]") {
    REQUIRE(ll.size() == 0);
}

TEST_CASE("check for element inserted at the beginning","[LinkedList<int>::insertBegin()]") {
    ll.insertEnd(10);
    ll.insertBegin(55);
    REQUIRE(*ll.begin() == 55);
}
