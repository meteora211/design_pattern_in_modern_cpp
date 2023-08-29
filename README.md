# design_pattern_in_modern_cpp

## Creational
### Builder
### Factories
### Prototype
### Singleton

## Structual
### Adapter
### Bridge
### Composite
### Decorator
### Facade
### Flyweight
### Proxy

### Summary
#### Proxy, Decorator, Adapter, and Bridge
from : https://stackoverflow.com/questions/350404/how-do-the-proxy-decorator-adapter-and-bridge-patterns-differ
> Proxy, Decorator, Adapter, and Bridge are all variations on "wrapping" a class. But their uses are different.

> Proxy could be used when you want to lazy-instantiate an object, or hide the fact that you're calling a remote service, or control access to the object.

> Decorator is also called "Smart Proxy." This is used when you want to add functionality to an object, but not by extending that object's type. This allows you to do so at runtime.

> Adapter is used when you have an abstract interface, and you want to map that interface to another object which has similar functional role, but a different interface.

> Bridge is very similar to Adapter, but we call it Bridge when you define both the abstract interface and the underlying implementation. I.e. you're not adapting to some legacy or third-party code, you're the designer of all the code but you need to be able to swap out different implementations.

> Facade is a higher-level (read: simpler) interface to a subsystem of one or more classes. Suppose you have a complex concept that requires multiple objects to represent. Making changes to that set of objects is confusing, because you don't always know which object has the method you need to call. That's the time to write a Facade that provides high-level methods for all the complex operations you can do to the collection of objects. Example: a Domain Model for a school section, with methods like countStudents(), reportAttendance(), assignSubstituteTeacher(), and so on.
