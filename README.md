# A Lora Serialization C library without dynamic allocation

This library provides functions to encode information according to the Lora
Serialization format.

This library is based on
[this implementation](https://github.com/thesolarnomad/lora-serialization) but
without any dynamic memory allocation.

## Build and run examples
Use `make`:

```
$ make example && ./examples/example 

> Temperature example
  Adding temperature: 35.40
  Encoded information: 0DD4

> Weather station example
  Adding time: 1535557041
  Adding position: 53.5570, 10.0229
  Adding temperature: 26.30
  Adding humidity: 37.60
  Adding humidity: 75
  Encoded information: B1BD865B08373103F4EF98000A46AF0E4B
```

## License
This library is licensed under LGPLv2.1.
