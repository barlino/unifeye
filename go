TI_VERSION=1.8.2
TI_SDK=/Users/barlino/Library/Application\ Support/Titanium/mobilesdk/osx/${TI_VERSION}
TITANIUM="${TI_SDK}/titanium.py"

make run 

cd ../ar 

python "${TITANIUM}" run --platform=iphone 

open build/iphone/ar.xcodeproj

cd ../unifeye
