#include "BinarySearchTree.hpp"

#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

TEST(BinarySearchTree_default_constructor) {
    BinarySearchTree<int> bst;
    ASSERT_TRUE(bst.empty());
    ASSERT_EQUAL(bst.size(), 0u);
    ASSERT_EQUAL(bst.height(), 0u);
    bst.insert(1);
    ASSERT_FALSE(bst.empty());
    ASSERT_EQUAL(bst.size(), 1u);
    ASSERT_EQUAL(bst.height(), 1u);
}

TEST(BinarySearchTree_insert) {
    BinarySearchTree<int> bst;
    bst.insert(1);
    ASSERT_FALSE(bst.empty());
    ASSERT_EQUAL(bst.size(), 1u);
    ASSERT_EQUAL(bst.height(), 1u);
    bst.insert(5);
    bst.insert(15);
    ASSERT_EQUAL(bst.size(), 3u);
    ASSERT_EQUAL(bst.height(), 3u);

    ASSERT_TRUE(bst.check_sorting_invariant());
} 

TEST(BinarySearchTree_copy_assignment_constructor) {
    BinarySearchTree<int> original_bst;
    original_bst.insert(10);
    original_bst.insert(5);
    original_bst.insert(15);
    original_bst.insert(3);
    original_bst.insert(7);
    ASSERT_TRUE(original_bst.check_sorting_invariant());

    BinarySearchTree<int> copied_bst(original_bst);
    BinarySearchTree<int> assigned_bst;
    assigned_bst = original_bst;
    ASSERT_EQUAL(copied_bst.size(), original_bst.size());
    ASSERT_EQUAL(copied_bst.height(), original_bst.height());

    ASSERT_EQUAL(assigned_bst.size(), original_bst.size());
    ASSERT_EQUAL(assigned_bst.height(), original_bst.height());

    auto original_it = original_bst.begin();
    auto copied_it = copied_bst.begin();
    auto assigned_it = assigned_bst.begin();
    while (original_it != original_bst.end() &&
           copied_it != copied_bst.end() &&
           assigned_it != assigned_bst.end()) {
        ASSERT_EQUAL(*original_it, *copied_it);
        ASSERT_EQUAL(*assigned_it, *copied_it);
        ++original_it;
        ++copied_it;
        ++assigned_it;
    }
}

TEST(BinarySearchTree_find) {
    BinarySearchTree<int> bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(13);
    bst.insert(17);

    auto it = bst.find(10);
    ASSERT_EQUAL(*it, 10);

    it = bst.find(5);
    ASSERT_EQUAL(*it, 5);

    it = bst.find(15);
    ASSERT_EQUAL(*it, 15);

    it = bst.find(3);
    ASSERT_EQUAL(*it, 3);

    it = bst.find(7);
    ASSERT_EQUAL(*it, 7);

    it = bst.find(13);
    ASSERT_EQUAL(*it, 13);

    it = bst.find(17);
    ASSERT_EQUAL(*it, 17);

    it = bst.find(1);
    ASSERT_EQUAL(it, bst.end());

    it = bst.find(6);
    ASSERT_EQUAL(it, bst.end());

    it = bst.find(11);
    ASSERT_EQUAL(it, bst.end());

    it = bst.find(14);
    ASSERT_EQUAL(it, bst.end());

    it = bst.find(18);
    ASSERT_EQUAL(it, bst.end());
}

TEST(BinarySearchTree_min_max) {
    BinarySearchTree<int> bst;
    ASSERT_EQUAL(bst.min_element(), bst.end());
    ASSERT_EQUAL(bst.max_element(), bst.end());
    ASSERT_EQUAL(bst.begin(), bst.end());

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(13);
    bst.insert(17);

    ASSERT_EQUAL(*bst.begin(), 3);
    ASSERT_NOT_EQUAL(bst.begin(), bst.end());
    ASSERT_TRUE(bst.check_sorting_invariant());

    ASSERT_EQUAL(*bst.min_element(), 3);
    ASSERT_EQUAL(*bst.max_element(), 17);

    ASSERT_EQUAL(*bst.min_greater_than(1), 3);
    ASSERT_EQUAL(*bst.min_greater_than(3), 5);
    ASSERT_EQUAL(*bst.min_greater_than(5), 7);
    ASSERT_EQUAL(*bst.min_greater_than(7), 10);
    ASSERT_EQUAL(*bst.min_greater_than(10), 13);
    ASSERT_EQUAL(*bst.min_greater_than(11), 13);
    ASSERT_EQUAL(*bst.min_greater_than(13), 15);
    ASSERT_EQUAL(*bst.min_greater_than(14), 15);
    ASSERT_EQUAL(*bst.min_greater_than(16), 17);
    ASSERT_EQUAL(bst.min_greater_than(17), bst.end());
    ASSERT_EQUAL(bst.min_greater_than(20), bst.end());
}

TEST(BinarySearchTree_os_copy_tests) {
    ostringstream oss;
    BinarySearchTree<int> bst;

    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(13);
    bst.insert(17);

    BinarySearchTree<int> copy_bst(bst);

    bst.traverse_inorder(oss);
    ASSERT_EQUAL(oss.str(), "3 5 7 10 13 15 17 ");
    oss.str("");
    copy_bst.traverse_inorder(oss);
    ASSERT_EQUAL(oss.str(), "3 5 7 10 13 15 17 ");

    oss.str("");

    bst.traverse_preorder(oss);
    ASSERT_EQUAL(oss.str(), "10 5 3 7 15 13 17 ");
    oss.str("");
    copy_bst.traverse_preorder(oss);
    ASSERT_EQUAL(oss.str(), "10 5 3 7 15 13 17 ");

    oss.str("");
    oss << bst;
    ASSERT_EQUAL(oss.str(), "[ 3 5 7 10 13 15 17 ]");
    oss.str("");
    oss << copy_bst;
    ASSERT_EQUAL(oss.str(), "[ 3 5 7 10 13 15 17 ]");
}

TEST(BinarySearchTree_copy_tests_edge_case) {
    BinarySearchTree<int> bst1;
    for (int i = 0; i<=6; i++) {
        bst1.insert(i);
    }

    BinarySearchTree<int> bst2;
    bst2.insert(3);
    bst2.insert(5);
    bst2.insert(1);
    bst2.insert(2);
    bst2.insert(4);
    bst2.insert(0);
    bst2.insert(6);
    // cout << bst1.to_string();
    // cout << bst2.to_string();

    ostringstream oss1;
    ostringstream oss2;

    bst1.traverse_inorder(oss1);
    bst2.traverse_inorder(oss2);
    ASSERT_EQUAL(oss1.str(), oss2.str());

    oss1.str("");
    oss2.str("");

    bst1.traverse_preorder(oss1);
    bst2.traverse_preorder(oss2);
    ASSERT_NOT_EQUAL(oss1.str(), oss2.str());

    BinarySearchTree<int> copy_bst2(bst2);

    oss1.str("");
    oss2.str("");

    bst2.traverse_preorder(oss1);
    copy_bst2.traverse_preorder(oss2);
    ASSERT_EQUAL(oss1.str(), oss2.str());
}

TEST_MAIN()
