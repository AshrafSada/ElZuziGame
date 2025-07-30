#include "GameInitializer.h"
#include <stdexcept>

int main( int argc, char* argv[] )
{
    try
    {
        GameInitializer gameInit{ };
        gameInit.RunGame( );
    }
    catch (const std::exception&)
    {
        return EXIT_FAILURE;
    }
    catch (const std::runtime_error&)
    {
        return EXIT_FAILURE;
    }
    catch (...)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
