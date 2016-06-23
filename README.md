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
