#include <CppBuildInfo/CompilerParserFactory.h>

#include "../gtestWrapper.h"

#include "tests_config.h"

namespace
{
    class CompilerParserGcc : public ::testing::Test
    {
    public:
        void SetUp() override
        {
            parser = createParser(CompilerType::GCC);
        }

        std::unique_ptr<ICompilerParser> parser;
    };

    const QString gccObjectFile(
        "/usr/bin/c++ -Dexiv2lib_STATIC -I. -I/media/linuxDev/programming/exiv2/build/src "
        "-Wall -Wcast-align -std=gnu++98 -fPIC -fvisibility=hidden -fvisibility-inlines-hidden -DXML_STATIC "
        "-o CMakeFiles/exiv2lib_int.dir/casiomn_int.cpp.o -c /media/linuxDev/programming/exiv2/src/casiomn_int.cpp "
        "1540478294436 1540478294937");

    const QString gccStaticLib(
        "/usr/bin/ar qc ../lib/libxmp.a CMakeFiles/xmp.dir/src/ExpatAdapter.cpp.o CMakeFiles/xmp.dir/src/MD5.cpp.o "
        "CMakeFiles/xmp.dir/src/ParseRDF.cpp.o CMakeFiles/xmp.dir/src/UnicodeConversions.cpp.o");

    const QString gccSharedLib(
        "/usr/bin/c++ -fPIC -Wall -std=gnu++98 -shared -Wl,-soname,libexiv2lib.so.0 -o ../lib/libexiv2lib.so.0.27.0.0 "
        "CMakeFiles/exiv2lib.dir/asfvideo.cpp.o CMakeFiles/exiv2lib.dir/basicio.cpp.o -L/path/to/zlib/ "
        "-L/path/to/gtest/ -L/path/to/expat/ -Wl,-rpath,/path/to/zlib/:/path/to/gtest/: ../lib/libxmp.a "
        "-ldl /path/to/zlib/libz.a -lpthread -lc");

    const QString gccApplication(
        "/usr/bin/c++ -Wall -W -std=gnu++98 -rdynamic CMakeFiles/exiv2json.dir/exiv2json.cpp.o "
        "CMakeFiles/exiv2json.dir/Jzon.cpp.o -o ../bin/exiv2json -L/path/to/zlib/lib -L/path/to/gtest/lib "
        "-L/path/to/Expat/lib -Wl,-rpath,/path/to/zlib/lib:/path/to/./gtest/lib:/path/to/Expat/lib:/path/myproject/build/lib: "
        "../lib/libexiv2lib.so.0.27.0.0 /path/to/zlib/lib/libz.a ../lib/libxmp.a /path/to/Expat/lib/libexpat.a");
}  // namespace

TEST_F(CompilerParserGcc, throwsIfGccIsNotInvolved)
{
    EXPECT_THROW(parser->parse("cl.exe troll mode"), std::runtime_error);
}

TEST_F(CompilerParserGcc, doesNotThrowWithCpp)
{
    EXPECT_NO_THROW(parser->parse("/usr/bin/c++ bla bla bla"));
}

TEST_F(CompilerParserGcc, doesNotThrowWithAr)
{
    EXPECT_NO_THROW(parser->parse("/usr/bin/ar bla bla bla"));
}

TEST_F(CompilerParserGcc, getSourceFile)
{
    auto unit = parser->parse(gccObjectFile);
    EXPECT_STREQ("/media/linuxDev/programming/exiv2/src/casiomn_int.cpp", unit.name.toLocal8Bit().constData());
    EXPECT_EQ(UnitType::SOURCE_FILE, unit.type);
}

TEST_F(CompilerParserGcc, getStaticLib)
{
    auto unit = parser->parse(gccStaticLib);
    EXPECT_STREQ("libxmp.a", unit.name.toLocal8Bit().constData());
    EXPECT_EQ(UnitType::STATIC_LIBRARY, unit.type);
}

TEST_F(CompilerParserGcc, getSharedLib)
{
    auto unit = parser->parse(gccSharedLib);
    EXPECT_STREQ("libexiv2lib.so.0", unit.name.toLocal8Bit().constData());
    EXPECT_EQ(UnitType::SHARED_LIBRARY, unit.type);
}

TEST_F(CompilerParserGcc, getApplication)
{
    auto unit = parser->parse(gccApplication);
    EXPECT_STREQ("exiv2json", unit.name.toLocal8Bit().constData());
    EXPECT_EQ(UnitType::APPLICATION, unit.type);
}
