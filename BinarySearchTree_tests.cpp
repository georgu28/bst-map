#include "BinarySearchTree.hpp"

#include "unit_test_framework.hpp"


TEST(BinarySearchTree_default_constructor) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.empty());
    ASSERT_EQUAL(bst.size(), 0u);
    ASSERT_EQUAL(bst.height(), 0u);
    bst.insert(1);
    ASSERT_FALSE(bst.empty());
    ASSERT_EQUAL(bst.size(), 1);
    ASSERT_EQUAL(bst.height(), 1);
}

TEST(BinarySearchTree_insert) {
    BinarySearchTree<int> bst;
    bst.insert(1);
    ASSERT_FALSE(bst.empty());
    ASSERT_EQUAL(bst.size(), 1);
    ASSERT_EQUAL(bst.height(), 1);
    bst.insert(5);
    bst.insert(15);
    ASSERT_EQUAL(bst.size(), 3);
    ASSERT_EQUAL(bst.height(), 3);
} 

TEST(BinarySearchTree_copy_constructor) {
    BinarySearchTree<int> original_bst;
    original_bst.insert(10);
    original_bst.insert(5);
    original_bst.insert(15);
    original_bst.insert(3);
    original_bst.insert(7);
    BinarySearchTree<int> copied_bst(original_bst);
    ASSERT_EQUAL(copied_bst.size(), original_bst.size());
    ASSERT_EQUAL(copied_bst.height(), original_bst.height());

    auto original_it = original_bst.begin();
    auto copied_it = copied_bst.begin();
    while (original_it != original_bst.end() && copied_it != copied_bst.end()) {
        ASSERT_EQUAL(*original_it, *copied_it);
        ++original_it;
        ++copied_it;
    }
}

TEST(BinarySearchTree_find) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);

    auto it = bst.find(10);
    ASSERT_NOT_EQUAL(it, bst.end());
    ASSERT_EQUAL(*it, 10);

    it = bst.find(5);
    ASSERT_NOT_EQUAL(it, bst.end());
    ASSERT_EQUAL(*it, 5);

    it = bst.find(15);
    ASSERT_NOT_EQUAL(it, bst.end());
    ASSERT_EQUAL(*it, 15);

    it = bst.find(1);
    ASSERT_EQUAL(it, bst.end());
}

TEST(BinarySearchTree_min_max) {
    BinarySearchTree<int> bst;
    ASSERT_EQUAL(bst.min_element(), bst.end());
    ASSERT_EQUAL(bst.max_element(), bst.end());

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);

    ASSERT_EQUAL(*bst.min_element(), 3);
    ASSERT_EQUAL(*bst.max_element(), 15);

    ASSERT_EQUAL(*bst.min_greater_than(3), 5);
    ASSERT_EQUAL(*bst.min_greater_than(7), 10);
    ASSERT_EQUAL(*bst.min_greater_than(1), 3);
    ASSERT_EQUAL(bst.min_greater_than(15), bst.end());
    ASSERT_EQUAL(bst.min_greater_than(20), bst.end());
}

TEST_MAIN()
