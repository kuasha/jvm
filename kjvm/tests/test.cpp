#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2.hpp"

#include "ClassHeap.h"
#include "JavaClass.h"

#define LIB_PATH "/home/boltu/workspaces/jvm/kjvm/lib"

TEST_CASE( "Load java/lang/String", "[ClassHeap]" ) {
    ClassHeap heap;
    heap.AddClassRoot(LIB_PATH);
    JavaClass klass;
    bool loaded = heap.LoadClass("java/lang/String", &klass);
    REQUIRE(loaded);
}
