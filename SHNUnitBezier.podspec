Pod::Spec.new do |s|
	s.name          = "SHNUnitBezier"
	s.version       = "1.0.1"
	s.summary       = "C based Unit Bezier solver/interpolator ported from WebKit for use on iOS and OS X"
	s.homepage      = "https://github.com/shnhrrsn/SHNUnitBezier"

	s.license       = "GNU General Public License"
	s.author        = "Shaun Harrison"

	s.source        = { :git => "https://github.com/shnhrrsn/SHNUnitBezier.git", :tag => "1.0.1" }
	s.source_files  = "*.{h,c}"
	s.requires_arc  = false
end
