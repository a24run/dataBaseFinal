cmake_minimum_required(VERSION 3.9)
project(sql_parser_1_5)

set(CMAKE_CXX_STANDARD 11)

add_executable(sql_parser_1_5
        main.cpp
        src/parser/bison_parser.cpp
        src/parser/bison_parser.h
        src/parser/flex_lexer.cpp
        src/parser/flex_lexer.h
        src/parser/parser_typedef.h
        src/sql/CreateStatement.h
        src/sql/DeleteStatement.h
        src/sql/DropStatement.h
        src/sql/ExecuteStatement.h
        src/sql/Expr.cpp
        src/sql/Expr.h
        src/sql/ImportStatement.h
        src/sql/InsertStatement.h
        src/sql/PrepareStatement.h
        src/sql/SelectStatement.h
        src/sql/SQLStatement.h
        src/sql/statements.cpp
        src/sql/statements.h
        src/sql/Table.h
        src/sql/UpdateStatement.h
        src/sqlhelper.cpp
        src/sqlhelper.h
        src/SQLParser.cpp
        src/SQLParser.h
        src/SQLParserResult.cpp
        src/SQLParserResult.h
        Makefile Main/input/input.cpp Main/input/input.h Main/output/create.cpp Main/actionFinder.cpp Main/headerFiles/actionFinder.h Main/headerFiles/create.h Main/output/select.cpp Main/headerFiles/select.h Main/output/insert.cpp Main/headerFiles/insert.h Main/catlog/catlog.cpp Main/headerFiles/catlog.h Main/catlog/tableClass.cpp Main/catlog/tableClass.h Main/managing/charTextManage.cpp Main/headerFiles/charTextManage.h Main/TblReadWrite/BinaryWrite.cpp Main/headerFiles/BinaryReadWrite.h Main/show/show.cpp Main/headerFiles/show.h Main/TblReadWrite/binaryRead.cpp Main/output/selectPrinter.cpp Main/output/selectPrinter.h Main/output/join.cpp Main/headerFiles/join.h Main/AdvanceSelects/orderBy.cpp Main/headerFiles/orderBy.h Main/AdvanceSelects/groupBy.cpp Main/headerFiles/groupBy.h Main/AdvanceSelects/joinON.cpp Main/headerFiles/joinON.h)
