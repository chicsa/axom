/*
 * Copyright (c) 2015, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * All rights reserved.
 *
 * This source code cannot be distributed without permission and
 * further review from Lawrence Livermore National Laboratory.
 */

#include "gtest/gtest.h"

#include "lumberjack/Message.hpp"

TEST(lumberjack_Message, getSet01)
{
    //Test most basic case: one text, one rank, file name, line number
    asctoolkit::lumberjack::Message m;
    m.text("I never wanted to do this job in the first place!");
    m.addRank(14, 5);
    m.fileName("foo.cpp");
    m.lineNumber(154);

    EXPECT_EQ(m.text(), "I never wanted to do this job in the first place!");
    EXPECT_EQ(m.fileName(), "foo.cpp");
    EXPECT_EQ(m.lineNumber(), 154);
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)1);
    EXPECT_EQ(m.ranksCount(), 1);
    EXPECT_EQ(m.ranks()[0], 14);
}

TEST(lumberjack_Message, getSet02)
{
    //Test that const char* will convert fine to string
    const char* textConstCharPointer = "I... I wanted to be... A LUMBERJACK!";
    std::string textString = "I... I wanted to be... A LUMBERJACK!";
    asctoolkit::lumberjack::Message m;
    m.text(textConstCharPointer);
    m.addRank(14, 5);

    EXPECT_EQ(m.text(), textString);
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)1);
    EXPECT_EQ(m.ranksCount(), 1);
    EXPECT_EQ(m.ranks()[0], 14);
}

TEST(lumberjack_Message, getSet03)
{
    //Test case: one text, filled ranks to rank limit
    const int ranksLimit = 5;
    asctoolkit::lumberjack::Message m;
    m.text("Leaping from tree to tree! As they float down the mighty rivers of British Columbia!");
    for(int i=0; i<(int)ranksLimit; ++i){
        m.addRank(i+1, ranksLimit);
    }

    EXPECT_EQ(m.text(), "Leaping from tree to tree! As they float down the mighty rivers of British Columbia!");
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)ranksLimit);
    EXPECT_EQ(m.ranksCount(), ranksLimit);
    for(int i=0; i<(int)ranksLimit; ++i){
        EXPECT_EQ(m.ranks()[i], i+1);
    }
}

TEST(lumberjack_Message, getSet04)
{
    //Test case: one text, filled ranks to past rank limit
    const int ranksLimit = 5;
    asctoolkit::lumberjack::Message m;
    m.text("With my best girl by my side!");
    for(int i=0; i<(int)ranksLimit*2; ++i){
        m.addRank(i+1, ranksLimit);
    }

    EXPECT_EQ(m.text(), "With my best girl by my side!");
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)ranksLimit);
    EXPECT_EQ(m.ranksCount(), (int)ranksLimit*2);
    for(int i=0; i<(int)ranksLimit; ++i){
        EXPECT_EQ(m.ranks()[i], i+1);
    }
}

TEST(lumberjack_Message, getSet05)
{
    //Test case: one text, fill ranks with vector of 1 rank
    const int ranksLimit = 5;
    std::vector<int> ranks;
    asctoolkit::lumberjack::Message m;
    m.text("The Larch! The Pine! The Giant Redwood tree! The Sequoia!");
    ranks.push_back(123);
    m.addRanks(ranks, 1, ranksLimit);

    EXPECT_EQ(m.text(), "The Larch! The Pine! The Giant Redwood tree! The Sequoia!");
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)1);
    EXPECT_EQ(m.ranksCount(), 1);
    EXPECT_EQ(m.ranks()[0], 123);
}

TEST(lumberjack_Message, getSet06)
{
    //Test case: one text, fill ranks with vector of ranks don't go past ranksLimit
    const int ranksLimit = 5;
    std::vector<int> ranks;
    asctoolkit::lumberjack::Message m;
    m.text("Oh, I'm a lumberjack, and I'm okay,");
    for(int i=0; i<(int)ranksLimit; ++i){
        ranks.push_back(i+1);
    }
    m.addRanks(ranks, ranksLimit, ranksLimit);

    EXPECT_EQ(m.text(), "Oh, I'm a lumberjack, and I'm okay,");
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)ranksLimit);
    EXPECT_EQ(m.ranksCount(), ranksLimit);
    for(int i=0; i<(int)ranksLimit; ++i){
        EXPECT_EQ(m.ranks()[i], i+1);
    }
}

TEST(lumberjack_Message, getSet07)
{
    //Test case: one text, fill ranks with vector of ranks that will go past ranksLimit
    const int ranksLimit = 5;
    std::vector<int> ranks;
    asctoolkit::lumberjack::Message m;
    m.text("I sleep all night and I work all day.");
    for(int i=0; i<(int)ranksLimit*3; ++i){
        ranks.push_back(i+1);
    }
    m.addRanks(ranks, ranksLimit*3, ranksLimit);

    EXPECT_EQ(m.text(), "I sleep all night and I work all day.");
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)ranksLimit);
    EXPECT_EQ(m.ranksCount(), (int)ranksLimit*3);
    for(int i=0; i<(int)ranksLimit; ++i){
        EXPECT_EQ(m.ranks()[i], i+1);
    }
}

TEST(lumberjack_Message, getSet08)
{
    //Test case: one text, add same rank multiple times to make sure ranks stays 1 but count increments
    const int ranksLimit = 5;
    std::vector<int> ranks;
    asctoolkit::lumberjack::Message m;
    m.text("This message is unimportant.");
    for(int i=0; i<(int)ranksLimit*3; ++i){
        m.addRank(1, ranksLimit);
    }

    EXPECT_EQ(m.text(), "This message is unimportant.");
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)1);
    EXPECT_EQ(m.ranksCount(), (int)ranksLimit*3);
    EXPECT_EQ(m.ranks()[0], 1);
}

TEST(lumberjack_Message, getSet09)
{
    //Test case: one text, fill ranks with vector of ranks that will go past ranksLimit
    const int ranksLimit = 5;
    std::vector<int> ranks;
    asctoolkit::lumberjack::Message m;
    m.text("This message is unimportant.");
    for(int i=0; i<(int)ranksLimit*3; ++i){
        ranks.push_back(1);
    }
    m.addRanks(ranks, ranksLimit*3, ranksLimit);

    EXPECT_EQ(m.text(), "This message is unimportant.");
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)1);
    EXPECT_EQ(m.ranksCount(), (int)ranksLimit*3);
    EXPECT_EQ(m.ranks()[0], 1);
}

TEST(lumberjack_Message, testConstructor01)
{
    //Test most basic case: one text, one rank, file name, line number
    asctoolkit::lumberjack::Message m("He's a lumberjack, and he's okay,",
                                      122, "foo.cpp", 154);

    EXPECT_EQ(m.text(), "He's a lumberjack, and he's okay,");
    EXPECT_EQ(m.fileName(), "foo.cpp");
    EXPECT_EQ(m.lineNumber(), 154);
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)1);
    EXPECT_EQ(m.ranksCount(), 1);
    EXPECT_EQ(m.ranks()[0], 122);
}

TEST(lumberjack_Message, testConstructor02)
{
    //Test most basic case: one text, one rank, file name, line number
    const int ranksLimit = 5;
    std::vector<int> ranks;
    for(int i=0; i<(int)ranksLimit; ++i){
        ranks.push_back(i+1);
    }

    asctoolkit::lumberjack::Message m("He sleeps all night and he works all day.",
                                      ranks, ranksLimit, ranksLimit, "foo.cpp", 154);

    EXPECT_EQ(m.text(), "He sleeps all night and he works all day.");
    EXPECT_EQ(m.fileName(), "foo.cpp");
    EXPECT_EQ(m.lineNumber(), 154);
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)ranksLimit);
    EXPECT_EQ(m.ranksCount(), ranksLimit);
    for(int i=0; i<(int)ranksLimit; ++i){
        EXPECT_EQ(m.ranks()[i], i+1);
    }
}

TEST(lumberjack_Message, stringOfRanks01)
{
    //Test most basic case: one rank
    const int ranksLimit = 5;
    asctoolkit::lumberjack::Message m;
    m.addRank(400, ranksLimit);

    EXPECT_EQ(m.text(), "");
    EXPECT_EQ(m.fileName(), "");
    EXPECT_EQ(m.lineNumber(), 0);
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)1);
    EXPECT_EQ(m.ranksCount(), 1);
    EXPECT_EQ(m.ranks()[0], 400);
    EXPECT_EQ(m.stringOfRanks(), "400");
}

TEST(lumberjack_Message, stringOfRanks02)
{
    //Test case: more than one rank
    const int ranksLimit = 5;
    std::vector<int> ranks;
    for(int i=0; i<(int)ranksLimit; ++i){
        ranks.push_back(i+1);
    }

    asctoolkit::lumberjack::Message m;
    m.addRanks(ranks, ranksLimit, ranksLimit);

    EXPECT_EQ(m.text(), "");
    EXPECT_EQ(m.fileName(), "");
    EXPECT_EQ(m.lineNumber(), 0);
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)ranksLimit);
    EXPECT_EQ(m.ranksCount(), ranksLimit);
    for(int i=0; i<(int)ranksLimit; ++i){
        EXPECT_EQ(m.ranks()[i], i+1);
    }
    EXPECT_EQ(m.stringOfRanks(), "1,2,3,4,5");
}

TEST(lumberjack_Message, stringOfRanks03)
{
    //Test case: full Message
    const int ranksLimit = 5;
    std::vector<int> ranks;
    for(int i=0; i<(int)ranksLimit; ++i){
        ranks.push_back(i*2);
    }

    asctoolkit::lumberjack::Message m("Unimportant message", ranks, ranksLimit, ranksLimit,
                                          "test/foo.cpp", 987654321);

    EXPECT_EQ(m.text(), "Unimportant message");
    EXPECT_EQ(m.fileName(), "test/foo.cpp");
    EXPECT_EQ(m.lineNumber(), 987654321);
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)ranksLimit);
    EXPECT_EQ(m.ranksCount(), ranksLimit);
    for(int i=0; i<(int)ranksLimit; ++i){
        EXPECT_EQ(m.ranks()[i], i*2);
    }
    EXPECT_EQ(m.stringOfRanks(), "0,2,4,6,8");
}

TEST(lumberjack_Message, pack01)
{
    //Test case: full Message
    const int ranksLimit = 5;
    std::vector<int> ranks;
    for(int i=0; i<(int)ranksLimit; ++i){
        ranks.push_back(i*2);
    }

    asctoolkit::lumberjack::Message m("Unimportant message", ranks, ranksLimit, ranksLimit,
                                          "test/foo.cpp", 987654321);

    EXPECT_EQ(m.text(), "Unimportant message");
    EXPECT_EQ(m.fileName(), "test/foo.cpp");
    EXPECT_EQ(m.lineNumber(), 987654321);
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)ranksLimit);
    EXPECT_EQ(m.ranksCount(), ranksLimit);
    for(int i=0; i<(int)ranksLimit; ++i){
        EXPECT_EQ(m.ranks()[i], i*2);
    }

    std::string packedMessage = m.pack();
    EXPECT_EQ(packedMessage, "0,2,4,6,8*5*test/foo.cpp*987654321*Unimportant message");
}

TEST(lumberjack_Message, unpack01)
{
    //Test case: full Message
    const int ranksLimit = 5;

    asctoolkit::lumberjack::Message m;
    m.unpack("0,2,4,6,8*15*test/foo.cpp*987654321*Unimportant message", ranksLimit);

    EXPECT_EQ(m.text(), "Unimportant message");
    EXPECT_EQ(m.fileName(), "test/foo.cpp");
    EXPECT_EQ(m.lineNumber(), 987654321);
    EXPECT_EQ(m.ranks().size(), (std::vector<int>::size_type)ranksLimit);
    EXPECT_EQ(m.ranksCount(), 15);
    for(int i=0; i<(int)ranksLimit; ++i){
        EXPECT_EQ(m.ranks()[i], i*2);
    }
}
