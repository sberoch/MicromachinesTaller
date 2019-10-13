#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Server/CarTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( CarTest );

using CppUnit::TestFactoryRegistry;

int main( int argc, char **argv) {
    CppUnit::TextUi::TestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();
    runner.addTest( registry.makeTest() );
    runner.run();
    return 0;
}
