# Contributing

## Styleguide

### Git commit message

* Use present tense ("Add feature" not "Added feature")
* Use imperative mood ("Move cursor to..." not "Moves cursor to...")
* Limit the first line to 72 characters or less
*
* When only changing documentation, include `[ci skip]` in the commit description
* Consider starting the commit message with an applicable emoji:
    * :art: : `:art:` when improving the format/structure of the code
    * :racehorse: : `:racehorse:` when improving performance
    * :non-potable_water: : `:non-potable_water:` when plugging memory leaks
    * :memo: : `:memo:` when writing docs
    * :penguin: : `:penguin:` when fixing something on Linux
    * :checkered_flag: `:checkered_flag` when fixing something on Windows
    * :bug: : `:bug:` when fixing a bug
    * :lock: : `:lock:` when dealing with security
    * :white_check_mark: : `:white_check_mark:` when adding tests
    * :green_heart: : `:green_heart:` when fixing the CI build
    * :fire: :  `:fire:` when removing code or files

### C++ Styleguide

#### Indentation

* Use 4 spaces instead of tabulation

#### Naming convention

* Names representing types must be in mixed case starting with uppercase.
```cpp
    Entity e;
    Map m;
```
* Variable names must be in mixed case starting with lowercase.
```cpp
    unsigned line;
    unsigned column
```
* Named constants (including enumeration values) must be all uppercase using undercore to separate words
```cpp
    #define PI 3.14
    #define COLOR_RED "#ff0000"
```
* Names representing methods or functions must be verbs and written in mixed case starting with lowercase
```cpp
    getName();
```
* Names representing namespaces should be all lowercase
```cpp
    std::cout << "Hello World" << std::endl;
```
* Names representing template types should be a single uppercase letter
```cpp
    template<class T>
```
* Abbreviations and acronyms must not be uppercase when used as name
```cpp
     saveJson(); // Not SaveJSON
```
* Private class variable should start with m_
```cpp
    class Class {
        private m_lenght;
    };
```
* Generic variables should have the same name as their types
```cpp
    void setSprite(Sprite* sprite); // Not void setSprite(Sprite* s);
```
* The name of the object is implicit, and should be avoided in a method name.
```cpp
    sprite.getTexture(); // Not sprite.getSpriteTexture();
```
* Plural form should be used on names representing a collection of object
```cpp
    vector<Entity> entities;
```
* The prefix is should be used for boolean variables and methods
```cpp
    boolean isVisible;
```
#### Files
* File content must be kept within 80 columns
* Header files must contain an include guard
```cpp
    #ifndef __FILE_H__
    #define __FILE_H__
    ...
    #endif /* __FILE_H__ */
```    
#### Statement

* The parts of a class must be sorted public, protected, private.
* Type convertions must always be done explicitly.
* Pointers and reference should have their reference symbol next to the type
```cpp
    float* x; // Not : float *x;
    int& y; // Not : int &y;
```
* The use of magic numbers in the code should be avoided. Numbers other than 0 and 1 should be considered declared as named constants instead.
* Floating point constants should always be written with decimal point and at least one decimal.
```cpp
    double speed = 0.0; // Not : double speed = 0;
    double speed = 3.0e8; // Not : double speed = 3e8;
```
* NO GOTO

#### Layout and Comments

* Block layout should be as illustred in example below
```cpp
    while(i < 0) {
        doSomething();
    }
```
* The class declaration should have the following form :
```cpp
    class MyClass : public MotherClass {
    public:
        ....
    protected:
        ....
    private:
        ....
    }
```
* Method definitions should have the following form:
```cpp
    void myMethod() {
        ....
    }
```
* The if-else class of statement should have the following form:
```cpp
    if (condition) {
        ....
    }
    else if (condition) {
        ....
    }
    else {
        ....
    }
```
* A for statement should have the following form:
```cpp
    for (unsigned i = 0; i < n; ++i) {
        ....
    }
```
* A while statement should have the following form:
```cpp
    while (condition) {
        ....
    }
```
* A do-while statement should have the following form:
```cpp
    do {
        ....
    } while (condition);
```
* A switch statement should have the following form:
```cpp
    switch (variable) {
        case A:
            ....
            break;
        case B:
            ....
            break;
        default:
            ....
            break;
    }
```
* A try-catch statement should have the following form:
```cpp
    try {
        ....
    }
    catch (Exception& exception) {
        ....
    }
```
* Variables in declarations can be left aligned.
* Use alignment wherever it enhances readability.
* Class and method header comments should follow the JavaDoc conventions.

### White space
* Conventional operators should be surrounded by a space character.
* C++ reserved words should be followed by a white space.
* Commas should be followed by a white space.
* Colons should be surrounded by white space.
* Semicolons in for statments should be followed by a space character.
