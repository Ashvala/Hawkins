# Hawkins
Hawkins takes JSON and makes it JUCE-y

### Proposal:
This is a project that allows you to define a layout in a JSON file and currently, some cursory callbacks for Button components.

The idea is to allow you to rapidly prototype interfaces and ideas. This is not a replacement to any layout mechanism that's currently in use.


#### JSON format:

This is an example of a painted text object

```json
    "text_obj": {
        "type": "painted_text",
        "position": {
            "x": 30,
            "y": 20
        },
        "size": {
            "width": 800,
            "height": 20
        },
        "font": "Avenir Heavy",
        "colour": [255, 255, 255],
        "text": "Hello, Hawkins",
        "font-size": 48.0
}

```

The fundamental basic attributes are:

- the `type` object typically reflects what kind of object is being rendered.

- the `position` object lets you assign the position of the object as integers. You have to set an `x` and `y` object along with the position.

- `size` allows you to define the bounds for an object that you render. You set a `width` and `height`.

- `colour` allows you to set a color as an array. Format is `[red, green, blue]`. All values are between 0 and 255.

The enumeration of types is as follows:

- painted_text
- painted_rect
- painted_ellipse
- component

`painted_text` allows you to additionally change the font and what the text is.

#### Components:

Currently, the one component that is supported is the Button. You can add buttons to your display.

Currently supported actions are:
- `openButtonPressed`, and
- `AnotherButtonPressed`

If you want to add custom callbacks, make sure you define them and call the `mapFunction` function that I've included. `mapFunction` maps a string to a function of type `void` with no inputs using `std::map`.

The map type is:

``` c++
typedef void(*func)();

std::map<std::string, std::function<void()>> hawkinsMap;

```

Using `func` as a function pointer with Hawkins map can be done as follows:

```c++
 mapFunction("anotherButtonPressed", buttonCallbacks::anotherButtonPressed);
```

Do keep in mind that using a function pointer can be limiting as you need to make sure that the function you're mapping it to is static.

However, on the flipside, you can use lambdas (yay!) to map functions, even within your own class:

```c++
mapFunction("helloworld",[&]{MainContentComponent::moveButtonPressed();});
```

The equivalent of this without the mapFunction sub routine would be:

```c++
hawkinsMap["helloworld"] = [&]{MainContentComponent::moveButtonPressed();};
```

### Component Animations:

You can animate components that you add.

An example of this from the Layout file is:

```json
"animation1":{
    "type": "animated",
    "component_to_animate": "open button",
    "animation_type": "move",
    "duration": 3000,
    "final_position": [400,400]
}
```

This allows you to move a component you've defined in the JSON file from wherever it was to wherever you want.

I will add a "fade" option soon.

### Future:

I think this can be used as an equivalent to Interface Builder in macOS and iOS SDKs. I will probably include an example of that in this project.

I am also going to look at better ways of creating a better mechanism to do things, without messing with MainContentComponent.

A fun exercise would be to try and create a JIT type thing where you update a JSON file and it reflects the changes on the screen.

#### TO-DO:

- SFINAE tests to make sure function exists.
