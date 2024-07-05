#pragma once
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "Machine.h"

TEST_CASE("Testing Register") {

    Register test;

    test.zero(0);
    CHECK(test.return_value(0) == 0);
    CHECK(test.size() == 1);

    test.zero(10);
    test.zero(30);
    test.zero(40);
    CHECK(test.size() == 4);

    test.inc(0);
    CHECK(test.return_value(0) == 1);

    test.zero(1);
    test.move(0, 1);
    CHECK(test.return_value(1) == 1);

    test.set(2, 6);
    CHECK(test.return_value(2) == 6);
}

TEST_CASE("Testing Machine") {

    Machine test;

    test.zero(0, 3);
    CHECK(test.get_reg(0) == 0);
    CHECK(test.get_reg(1) == 0);
    CHECK(test.get_reg(2) == 0);

    test.set(0, 3);
    CHECK(test.get_reg(0) == 3);

    test.copy(0, 1, 1);
    CHECK(test.get_reg(1) == 3);

    test.zero(0, 5);
    test.set(0, 3);
    test.set(1, 3);
    test.set(2, 3);
    test.set(3, 4);
    test.set(4, 4);
    test.set(5, 4);

    test.copy(0, 3, 3);
    CHECK(test.get_reg(3) == 3);
    CHECK(test.get_reg(4) == 3);
    CHECK(test.get_reg(5) == 3);

    test.qoute("ZERO 3");
    test.get_operator(test.get_last_instruct_num() - 1);

    std::ifstream file("add.urm");
    test.load(file);
    file.close();
    CHECK(test.get_operator(0).first == "ZERO 3");
    CHECK(test.get_operator(0).second == 0);
    CHECK(test.get_operator(5).first == "JUMP 2");
    CHECK(test.get_operator(5).second == 5);
    test.zero(0, 2);
    test.set(0, 3);
    test.set(1, 6);
    test.run_instructions();
    CHECK(test.get_reg(2) == 9);
}
void runtests() {
    doctest::Context().run();
}