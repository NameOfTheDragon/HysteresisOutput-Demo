#include <Arduino.h>
#include <Timer.h>
#include <HysteresisOutput.h>

constexpr Duration minimumOnTime = Timer::Seconds(5);
constexpr Duration minimumOffTime = Timer::Seconds(10);

bool inputState;

void stateChanger(bool state)
{
  Serial.print("State changed to ");
  Serial.println(state);
}

// The folowing definition contains a lambda expression (advanced C++)
HysteresisOutput demo(minimumOnTime, minimumOffTime, [](bool state)
                      { stateChanger(state); });

Timer simulateRandomInput;

void setup()
{
  simulateRandomInput.setDuration(Timer::Seconds(1));
}

void loop()
{
  demo.loop();
  if (simulateRandomInput.expired())
  {
    Duration randomDuration = Timer::Milliseconds((int)random(1000, 20000));
    simulateRandomInput.setDuration(randomDuration);
    inputState = !inputState;
    Serial.print("Input state -> ");
    Serial.println(inputState);
    demo.setInputState(inputState);
  }
}