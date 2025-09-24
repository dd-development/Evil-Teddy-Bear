# Evil Teddy Bear
An embedded project utilizing 4 Arduino UNO boards and C++ to create a novelty Evil Teddy Bear toy.

## DEMO VIDEO


## Overview and Design
The Evil Teddy Bear is a horror-inspired toy designed with 4 Arduino UNO boards that communicate using I2C to coordinate and control multiple different mechanical and audiovisual devices attached to the bear.

The bear has 2 menacing red LED eyes that will turn on upon powering it. In order to enable movement, 3 vibrating disc motors and a small servomotor were woven into the bear. A DF Player Mini chip along with a
small 3W speaker and an SD card were used to store and play audio files that I voiced and pre-recorded so the bear had a variety of dialogue it could communicate to the user. An ultrasonic sensor was also used to detect
user interaction with the toy, along with an LCD screen and a button for information, debugging, and reset purposes.

**The Evil Teddy Bear has 5 "scariness" levels that change depending on user interaction:**

1. **None:** The user has just powered the toy on. The bear is friendly and encourages the user to interact with it. The bear's head moves back and forth slightly.
2. **Weird:** The user has interacted with the bear a little bit. The bear starts to say clingy and slightly perturbing things such as "Don't leave me!" and "Are you afraid?"
3. **Scary:** The user has interacted with the bear for awhile. The bear's voice becomes disembodied and unsettling, saying frightening and vaguely threatening things like "No matter where you go, I'll find you..."
4. **Terrifying:** The user has interacted with the bear for a long time. The bear's voice becomes distorted, saying horrifying and outright threatening things like "I'm gonna chew on your face!" The bear also starts vibrating violently.
5. **Unintelligible Screaming:** The user has continued to interact with the bear despite its warnings. The bear begins to screech extremely loudly in a very distorted, horrifying tone. It continues to vibrate violently.

**Each Arduino board controls different aspects of the bear's functionality:**
* The **master** board utilizes an ultrasonic sensor to detect user interaction with the toy. As the user interacts with the bear through touch, the master board updates the scariness level and sends it to each of the other boards. The LCD screen displays the bear's current scariness level, and the button resets it back to no scariness.
* The **buzzer** board controls the vibrating disc motors and the servo motor, updating their behavior based on the bear's scariness level.
* The **audio** board controls the DF Player Mini chip and the speaker. It updates and outputs the bear's dialogue audio from an SD card based on the bear's current scariness level.
* The **LED** board controls the red LEDs for the bear's eyes.

## Example
![bear front2](https://github.com/user-attachments/assets/d7f8ddcb-54a8-48e6-be55-e657d51e0a9f)

![bear back](https://github.com/user-attachments/assets/e4eccea3-2623-4058-95b8-f751536db85c)

<img width="1000" height="1000" alt="full diagram" src="https://github.com/user-attachments/assets/80bfe085-79f8-497e-97b1-5ddbc4b5c557" />
