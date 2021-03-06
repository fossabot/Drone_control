#include "LEDManager.h"

std::unique_ptr<Led> LEDManager::get_led()
{
    if (get_navio_version() == NAVIO2)
    {
        auto ptr = std::unique_ptr<Led>{new Led_Navio2()};
        return ptr;
    }
    else
    {
        auto ptr = std::unique_ptr<Led>{new Led_Navio()};
        return ptr;
    }
}

LEDManager::LEDManager()
{
    if (!led->initialize())
    {
        std::cout << "[ LEDManager ] : Cannot initialize ...\n";
        throw EXIT_FAILURE;
    }
    setKO();
    std::cout << "[ LEDManager ] : Starting ...\n";
}

void LEDManager::update()
{
    if (mode == 1 && updateIter == 0) // mode ok and start of the loop
    {
        led->setColor(Colors::Green);
    }

    if (mode == 2 && updateIter == 0) // mode arming and start of the loop
    {
        led->setColor(Colors::Cyan);
    }
    if ((mode == 1 || mode == 2) && updateIter == rate)
    {
        led->setColor(Colors::Black);
    }

    updateIter++;

    if (updateIter > 2 * rate)
    {
        updateIter = 0;
    }
}

void LEDManager::setKO()
{
    mode = 0;
    led->setColor(Colors::Red);
}

void LEDManager::setOK()
{
    mode = 1; // blinking state
}

void LEDManager::setArmed()
{
    mode = 3;
    led->setColor(Colors::Blue);
}

void LEDManager::setBlack()
{
    mode = 0;
    led->setColor(Colors::Black);
}

void LEDManager::setArming()
{
    mode = 2; // blinking state
}

void LEDManager::backToPrevious()
{ // prevent deleting KO state
    if (mode > 0)
    {
        mode = 1;
    }
}
