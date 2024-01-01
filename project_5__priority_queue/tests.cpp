#include <gtest/gtest.h>
#include "priorityqueue.h"
#include <vector>
#include <map>
#include <stdlib.h>
#include <string>
#include <sstream>

// Test for enqueue, begin, next, Size
TEST(priorityqueue, nextTest){
    priorityqueue<double> project;
    int size = 0;
    for (int i = 0; i <= 99; i++) {
        project.enqueue((double)rand(), rand() % 10);
        size++;
        ASSERT_EQ(project.Size(), size);
    }
    double x = 2.2;
    project.begin();
    for (int i = 0; i <= 98; i++) {
        ASSERT_EQ(project.next(x, size), true);
    }
    // Checking that there's no bugs for next
    for (int i = 0; i <= 98; i++) {
        ASSERT_EQ(project.next(x, size), false);
    }
}

// Test for enqueue, dequeue
TEST(priorityqueue, enqueueStringDequeueSize) {
    vector<string> lts = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
    "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    int l = 16;
    priorityqueue<string> tree;

    for (int i = 0; i <= 99; i++) {
        tree.enqueue(lts[i % 26], rand());
        string str = lts[i % 26];
        ASSERT_EQ(tree.dequeue(), str);
    }
    // cout << tree.toString() << endl;
    ASSERT_EQ(tree.Size(), 0);
}

// Example from Priorityqueue pdf
TEST(priorityqueue, exampleTest) {
    map<int, vector<int> > map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }
    EXPECT_EQ(pq.Size(), 9);
    stringstream ss;
    for (auto e: map) {
    int priority = e.first;
    vector <int> values = e.second;
        for (size_t j = 0; j < values.size(); j++) {
            ss << priority << " value: " << values[j] << endl;
        }
    }
    EXPECT_EQ(pq.toString(), ss.str());
}

// Asserts for enqueue string, dequeue small tree with edge cases and duplicates
TEST(priorityqueue, enqueueStringDequeueWithDuplicatesSize) {
    priorityqueue<string> lightBlue;

    map<int, string> safeWords;

    safeWords[-1] = "red";
    safeWords[0] = "yellow";
    safeWords[1] = "green";

    for (int i = 1; i <= 3; i++) {
        lightBlue.enqueue(safeWords[-1] , -7);
    }

    for (int i = 1; i <= 2; i++) {
        lightBlue.enqueue(safeWords[0] , 0);
    }

    for (int i = 1; i <= 3; i++) {
        lightBlue.enqueue(safeWords[1] , 3);
    }
    // cout << lightBlue.toString() << endl;
    string myStr = safeWords[-1];
    while (lightBlue.Size()) {
        if (lightBlue.Size() >= 6 && lightBlue.Size() <= 8) {
            ASSERT_EQ(myStr, lightBlue.dequeue());
        }

        else if (lightBlue.Size() >= 4 && lightBlue.Size() <= 5) {
            myStr = safeWords[0];
            ASSERT_EQ(myStr, lightBlue.dequeue());
        }

        else {
            myStr = safeWords[1];
            ASSERT_EQ(lightBlue.dequeue(), myStr);
        }
    }
    // ASSERT_EQ(lightBlue.dequeue() == myStr, true);
}

// Testing large data
// Asserts for enqueue string, begin and next, Size
TEST(priorityqueue, enqueueStringBeginNextSize) {
    map<int, string> game;

    vector<string> safeWords = {"red", "yellow", "green"};

    for (int i = 0; i <= 100000; i++) {
        game[i] = safeWords[i % 3];
    }
    // map should, in theory, reject duplicates, check size
    int t = game.size();

    priorityqueue<string> darkBlue;
    // hopefully, using rand again the same way results in collisions so we can
    // obtain duplicates for the priorityqueue
    for (auto &pair : game) {
        // if (pair.first % 2 == 0) {
        //     if ((rand() % 99) % 2 == 0) {
        //         darkBlue.enqueue(pair.second, pair.first % 2);
        //         // ASSERT_EQ(darkBlue.dequeue(), pair.second - 1);
        //     }
        //     // else {
        //     //     darkBlue.enqueue(pair.second, pair;
        //     // }
        // }
        // else {
        //     darkBlue.enqueue(pair.second, pair.first);
        // }
        if (pair.first % 2 == 0) {
            darkBlue.enqueue(pair.second, pair.first % 2);
        }
    }
    // check quickly if there's some duplicates
    cout << darkBlue.toString() << endl;
    cout << darkBlue.Size() << endl;
    // ASSERT_EQ(darkBlue.Size(), t);
    // Assertion for begin and next. Should be false for t and after it.
    darkBlue.begin();
    string s = "check";
    int n = 3;
    // cout << "size" << darkBlue.Size() << " " << game.size() << endl;
    for (int i = 1; i <= t - 1; i++) {
        ASSERT_EQ(darkBlue.next(s, n), true);
    }
    for (int i = 0; i <= 11; i++) {
        ASSERT_EQ(darkBlue.next(s, n), false);
    }
}

// This test asserts enqueue string, size, copy and equality operator's, begin
// and next, clear
TEST(priorityqueue, enqueueStringCopyOpEqualityOpBeginNextClearSize) {
    priorityqueue<string> beatles;

    vector<string> song = {"you", "say", "goodbye", "and", "I", "hello"};

    for (int i = 0; i <= 19; i++) {
        for (int j = 0; j <= 5; j++) {
            if (j % 2 == 1) {
                if (j == 5) {
                    beatles.enqueue(song[1], (i * j) % 5);
                }
                beatles.enqueue(song[j], (i * j) % 5);
            }

            else {
                beatles.enqueue(song[j], i % (j + 19));
            }
        }
    }

    // cout << beatles.toString() << endl;  uncomment to see output

    int length = 6 * 20 + 5 * 4;

    ASSERT_EQ(beatles.Size(), length);
    // assertion for copy and equality operator's
    priorityqueue<string> clone;

    clone = beatles;

    ASSERT_EQ(clone == beatles, true);

    string arbitrary = "proof by contradiction";

    int n = 3;
    // Assertion for begin and next
    clone.begin();

    for (int i = 0; i <= 138; i++) {
        ASSERT_EQ(clone.next(arbitrary, n), true);
    }
    // Important, next needs to be false for any number of calls afterwards.
    // I.e. curr = nullptr
    // I failed to test this early on and failed professor's tests
    for (int i = 0; i <= 251; i++) {
        ASSERT_EQ(clone.next(arbitrary, n), false);
    }

    clone.clear();

    ASSERT_EQ(clone.Size(), 0);
}

TEST(priorityqueue, enqueueStringBeginNextSizeWithDuplicates) {
    vector<string> youAreAmazing = {"na", "that", "feel", "me", "make", "you"};

    priorityqueue<string> inspire;

    int j = 5;
    for (int i = 0; i <= 5; i++) {
        inspire.enqueue(youAreAmazing[j], i);
        j--;
    }

    j = 5;

    for (int i = 0; i <= 3; i++) {
        inspire.enqueue(youAreAmazing[0], 5);
    }

    // cout << inspire.toString() << endl; please uncomment to see : )

    ASSERT_EQ(inspire.Size(), 10);

    string s = "the good kind of bad is an example of overloading";

    int v = 1;

    inspire.begin();

    for (int i = 0; i <= 8; i++) {
        ASSERT_EQ(inspire.next(s, v), true);
    }
    // checking next for false.
    for (int i = 0; i <= 90; i++) {
        ASSERT_EQ(inspire.next(s, v), false);
    }
}

TEST(priorityqueue, enqueueStringDequeueSizeWithoutDuplicates) {
    vector<string> overLoading = {"The", "climax", "was", "during", "edge", 
    "cases"};

    priorityqueue<string> o;

    for (int i = 0; i <= 5; i++) {
        o.enqueue(overLoading[i], i);
    }

    // cout << inspire.toString() << endl; please uncomment to see

    ASSERT_EQ(o.Size(), 6);
    int n = 6;
    for (int i = 0; i <= 5; i++) {
        string valueOut = overLoading[i];
        ASSERT_EQ(o.dequeue(), valueOut);
         // checking that size decrements for each dq
        ASSERT_EQ(o.Size(), n - i - 1);
    }
    // checking that dq did it's job with regard to Size
    ASSERT_EQ(o.Size(), 0);
}

TEST(priorityqueue, defaultConstructorInt) {
    priorityqueue<int> myQueue;

    ASSERT_EQ(myQueue.getRoot(), nullptr);
    ASSERT_EQ(myQueue.Size(), 0);
    ASSERT_EQ(myQueue.toString(), "");
}

TEST(priorityqueue, defaultConstructorString) {
    priorityqueue<string> mq;

    ASSERT_EQ(mq.getRoot(), nullptr);
    ASSERT_EQ(mq.Size(), 0);
    ASSERT_EQ(mq.toString(), "");
}

// Empty, we add a node
TEST(priorityqueue, enqueueIntEmpty) {
    priorityqueue<int> mq;

    mq.enqueue(1, 1);

    ASSERT_EQ(mq.Size(), 1);
    // EXPECT_EQ(mq.getRoot(), &mq);
    ASSERT_EQ(mq.toString(), "1 value: 1\n");
}

// Nonempty, insert left
TEST(priorityqueue, enqueueIntNonempty) {
    priorityqueue<int> mq;

    mq.enqueue(1, 2);
    mq.enqueue(1, 1);    // lower priority (value, priority)

    ASSERT_EQ(mq.Size(), 2);
}

TEST(priorityqueue, toStrEmpty) {
    priorityqueue<string> pq;

    ASSERT_EQ(pq.toString(), "");
}

TEST(priorityqueue, toStrNonEmptyString) {
    priorityqueue<string> pq;

    pq.enqueue("Dolores", 5);
    pq.enqueue("Bernard", 4);
    pq.enqueue("Arnold", 8);
    pq.enqueue("William", 5);
    pq.enqueue("Teddy", 5);
    pq.enqueue("Ford", 2);

    ASSERT_EQ(pq.Size(), 6);

    // insertion order for duplicates, in order traversal
    string myStr = "2 value: Ford\n4 value: Bernard\n5 value: Dolores\n";
    myStr += "5 value: William\n5 value: Teddy\n8 value: Arnold\n";

    ASSERT_EQ(pq.toString(), myStr);
}

TEST(priorityqueue, clearInt) {
    priorityqueue<int> pq;

    pq.enqueue(1, 2);
    pq.enqueue(1, 1);
    pq.enqueue(1, 3);
    pq.enqueue(1, 4);
    pq.enqueue(5, 2);
    pq.enqueue(6, 2);
    pq.toString();
    pq.clear();     // causes a valgrind error like double free
    // pq.toString();
    ASSERT_EQ(pq.Size(), 0);
    ASSERT_EQ(pq.toString(), "");
}

TEST(priorityqueue, operatorEqualityItselfInt) {
    priorityqueue<int> pq;

    ASSERT_EQ(pq, pq);
}

TEST(priorityqueue, operatorEqualityNewObjectInt) {
    priorityqueue<int> pq;
    priorityqueue<int> nq;

    pq.enqueue(0, 2);
    nq.enqueue(0, 2);

    pq.enqueue(1, 2);   // duplicate
    nq.enqueue(1, 2);

    pq.enqueue(2, 2);

    pq.enqueue(0, 1);
    nq.enqueue(0, 1);

    pq.enqueue(0, 3);
    nq.enqueue(0, 3);

    ASSERT_EQ(pq == nq, false);
}
// Failing
// TEST(priorityqueue, nextExamplePriority) {
//     priorityqueue<int> pq;
//     // pq.enqueue(0,5);
//     // pq.enqueue(0,4);
//     // pq.enqueue(0,2);
//     pq.enqueue(0,8);
//     pq.enqueue(0,8);
//     //pq.enqueue(0,8);
//     // pq.enqueue(0,6);
//     // pq.enqueue(0,11);

//     pq.begin();
//     int x = 0, y = 8;
//     ASSERT_EQ(pq.next(x, y), true);
//     ASSERT_EQ(pq.next(x,y), false);

//     // int r = 0, s = 5;
//     // ASSERT_EQ(pq.next(r, s), true);
//     // r = 0, s = 4;
//     // ASSERT_EQ(pq.next(r, s), true);
//     // r = 0, s = 2;
//     // ASSERT_EQ(pq.next(r, s), true);
//     // r = 0, s = 8;
//     // ASSERT_EQ(pq.next(r, s), true);
//     // r = 0, s = 8;
//     // ASSERT_EQ(pq.next(r, s), true);
//     // r = 0, s = 8;
//     // ASSERT_EQ(pq.next(r, s), true);
//     // r = 0, s = 6;
//     // ASSERT_EQ(pq.next(r, s), true);
//     // r = 0, s = 11;
//     // ASSERT_EQ(pq.next(r, s), false);
// }
// I need not touch this test.
// TEST(priorityqueue, nextTesting) {
//     priorityqueue<int> pq;
//     pq.enqueue(0,5);
//     pq.enqueue(0,4);
//     pq.enqueue(0,2);
//     pq.enqueue(0,8);
//     pq.enqueue(0,6);
    
//     pq.begin();
//     int x = 0, y = 8;
//     ASSERT_EQ(pq.next(x, y), false);
// }
TEST(priorityqueue, copyOperatorEqualityDuplicatesString) {
    priorityqueue<string> pq;
    pq.enqueue("Deloris", 5);
    pq.enqueue("Melinda", 4);
    pq.enqueue("Arnold", 8);
    pq.enqueue("William", 5);
    pq.enqueue("Teddy", 5);
    pq.enqueue("Jack", 2);
    pq.enqueue("thing", 5);

    // cout << "original" << endl;
    pq.toString();

    priorityqueue<string> nq;
    nq = pq;
    // cout << "clone" << endl;
    nq.toString();

    ASSERT_EQ(nq.Size(), pq.Size());
    // ASSERT_EQ(nq.toString(), pq.toString());
    ASSERT_EQ(nq == pq, true);
}
// Awesome test for valgrind error
TEST(priorityqueue, copyOperator) {
    priorityqueue<string> pq;
    pq.enqueue("Deloris", 5);

    priorityqueue<string> nq;
    nq = pq;
}

TEST(priorityqueue, nextDuplicates) {
    priorityqueue<string> pq;
    pq.enqueue("Deloris", 5);
    pq.enqueue("Matthew", 5);

    string r = "asdf";
    int t = 0;

    //pq.begin();
    //pq.next(r, t);
    ASSERT_EQ(pq.next(r, t), false);
}

TEST(priorityqueue, dequeueWithDuplicates) {
    priorityqueue<string> pq;
    pq.enqueue("Bert", 0);
    pq.enqueue("Alex", 1);
    pq.enqueue("Megan", 0);
    pq.enqueue("Dolores", 2);
    pq.enqueue("Bernard", 2);
    pq.enqueue("Stephen", 2);
    pq.enqueue("Agnes", 2);
    // pq.enqueue("Bob", -2);
    //pq.enqueue("Stephanie", -2);

    // while (pq.Size() >= 1) {
    //     cout << "size " << pq.Size() << endl;
    //     cout << pq.dequeue() << endl;
    // }
    // cout << pq.Size() << endl;
}
/*
        6
    4       8
2-2-2      5 7       11

*/

TEST(priorityqueue, next) {
    priorityqueue<string> pq;
    pq.enqueue("Deloris", 5);
    pq.enqueue("Janet", 5);
    pq.enqueue("Bernard", 5);
    pq.enqueue("Jane", 5);
    pq.enqueue("Ford", 2);
    pq.enqueue("Lola", 2);
    // pq.enqueue("Melissa", 3);
    // pq.enqueue("Arnold", 8);
    // pq.enqueue("William", 8);
    // pq.enqueue("Teddy", 8);
    // pq.enqueue("Jasmine", 7);
    // pq.enqueue("Carlos", 11);
    // pq.enqueue("New node", 5);
    // pq.enqueue("Some node", 11);
    // pq.enqueue("Other node", 11);

    pq.begin();
    string s = "Deloris";
    int p = 5;
    int i = 1;
    // while (pq.next(s,p)) {
    //     cout << pq.next(s, p) << endl;
    // }
    // cout << pq.next(s, p) << endl;
}

// Verified passing
TEST(priorityqueue, dequeueWithoutDuplicates) {
    priorityqueue<string> pq;
    pq.enqueue("Dolores", 10);
    pq.enqueue("Bernard", 20);
    pq.enqueue("Ford", 11);
    pq.enqueue("Elaine", 11);
    pq.enqueue("Jerry", 10);
    pq.enqueue("Stephanie", 21);
    pq.enqueue("some node", 21);
    pq.enqueue("Ludwig", 21);
    pq.enqueue("Costanza", 5);
    pq.enqueue("Steinbrenner", 5);
    pq.enqueue("Joanna", 1);

    // while (pq.Size()) {
    //     cout << pq.dequeue() << endl;
    // }
    // cout << pq.Size() << endl;
    // cout << pq.dequeue() << endl;
    // cout << pq.Size() << endl;
}

TEST(priorityqueue, peek) {
    priorityqueue<string> pq;

    pq.enqueue("Dolores", 10);
    pq.enqueue("Bernard", 20);
    pq.enqueue("Ford", 11);
    pq.enqueue("Elaine", 11);
    pq.enqueue("Jerry", 10);
    pq.enqueue("Stephanie", -21);
    pq.enqueue("some node", 21);
    pq.enqueue("Ludwig", 21);
    pq.enqueue("Costanza", 5);
    pq.enqueue("Steinbrenner", 5);
    pq.enqueue("Joanna", 1);
    // cout << pq.peek() << endl;
}
