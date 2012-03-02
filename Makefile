PROJECT_ROOT=$(shell pwd)
TI_VERSION=1.8.2
TI_SDK="/Users/barlino/Library/Application Support/Titanium/mobilesdk/osx/${TI_VERSION}"
TITANIUM="${TI_SDK}/titanium.py"
run:
#module:
	@echo "[Building Titanium Module for iOS]"
	@echo $(shell "${PROJECT_ROOT}"/build.py)
#deploy:
	@echo [Copy com.otiga.unifeye.a into Ti project for testing]
	@echo /bin/cp -f build/libcom.otiga.unifeye.a ../ar/modules/iphone/com.otiga.unifeye/0.1/
	@echo $(shell /bin/cp -f build/libcom.otiga.unifeye.a ../ar/modules/iphone/com.otiga.unifeye/0.1/)

	@echo [Copy app.js into Ti project for testing]
	@echo /bin/cp -f example/app.js ../ar/Resources/ 
	@echo $(shell /bin/cp -f example/app.js ../ar/Resources/)

	@echo [Copy module.zip into Ti project for testing]
	@echo /bin/cp -f com.otiga.unifeye-iphone-0.1.zip ../ar/Resources/ 
	@echo $(shell /bin/cp -f com.otiga.unifeye-iphone-0.1.zip ../ar/)

# @echo [Build XCode Project]
# @cd ../ar
# @echo python "${TITANIUM}" run --platform=iphone --dir=../ar
# @echo $(shell python "${TITANIUM}" run --platform=iphone)

# @echo "[Open XCode Project]"
# @echo $(shell open ../ar/build/iphone/ar.xcodeproj/)
# @cd "${PROJECT_ROOT}"
clean:
	@echo "Performing clean build"
	@cd "${PROJECT_ROOT}"
	@rm -rfv com.otiga.unifeye-iphone-0.1.zip