# SHNUnitBezier

C based Unit Bezier solver/interpolator ported from WebKit for use on iOS/OS X

## Usage

```c
// Setup some predefined values
const double from = 0.0;
const double to = 10.0;

double duration = 1.0;
double time = 0.3;

double current;

// Using predefined bezier curves:
current = SHNUnitBezierInterpolate(SHNUnitBezierEaseInOut, time / duration, duration, from, to);
NSLog(@"Ease in/out: %.03f", current); // Ease in/out: 1.872

current = SHNUnitBezierInterpolate(SHNUnitBezierEaseIn, time / duration, duration, from, to);
NSLog(@"Ease in: %.03f", current); // Ease in: 1.290

current = SHNUnitBezierInterpolate(SHNUnitBezierEaseOut, time / duration, duration, from, to);
NSLog(@"Ease out: %.03f", current); // Ease out: 4.460

// Using a linear curve:
current = SHNUnitBezierInterpolate(SHNUnitBezierLinear, time / duration, duration, from, to);
NSLog(@"Linear: %.03f", current); // Linear: 3.047

// Or, using a custom bezier curve:
current = SHNUnitBezierInterpolate(SHNUnitBezierMake(0.4, 0.01, 0.16, 1.0), time / duration, duration, from, to);
NSLog(@"Custom: %.03f", current); // Custom: 3.992
```

## License

GNU General Public License (inherited from WebKit)
