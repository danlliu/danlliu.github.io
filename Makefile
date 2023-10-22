
SRC = src
SRC_ASSETS = $(SRC)/assets
SRC_DATA = $(SRC)/data
SRC_TEMPLATES = $(SRC)/templates
SRC_CSS = $(SRC)/css
SRC_JS = $(SRC)/js
SRC_CPP = $(SRC)/cpp

BUILD_DIR = build
BUILD_ASSETS = $(BUILD_DIR)/assets
BUILD_CSS = $(BUILD_DIR)/style
BUILD_JS = $(BUILD_DIR)/script

IN_HTML_FILES = $(wildcard $(SRC_TEMPLATES)/*.html)

IN_CSS_FILES = $(wildcard $(SRC_CSS)/*.css)
OUT_CSS_FILES = $(IN_CSS_FILES:src/css/%.css=build/style/%.css)

IN_JS_FILES = $(wildcard $(SRC_JS)/*.js)
OUT_JS_FILES = $(IN_JS_FILES:src/js/%.js=build/script/%.js)

COPIED_ASSETS = github.png

SERVERPORT = 8000

release: build assets html css js wasm

build:
	@mkdir $(BUILD_DIR)
	@mkdir -p $(BUILD_ASSETS)
	@mkdir -p $(BUILD_CSS)
	@mkdir -p $(BUILD_JS)

############
## Assets ##
############

$(SRC_ASSETS)/dl_ascii.txt: $(SRC_ASSETS)/dl.txt
	convert -size 360x360 xc:white -font "MesloLGLDZ-Nerd-Font-Mono-Regular" -pointsize 256 -fill black -draw @$(SRC_ASSETS)/dl.txt $(SRC_ASSETS)/image.jpg
	jp2a --size=38x19 --invert $(SRC_ASSETS)/image.jpg > $@

$(BUILD_DIR)/resume.pdf: $(SRC_ASSETS)/resume.pdf
	cp $< $@

.PHONY: copied_assets
copied_assets: $(COPIED_ASSETS:%=$(SRC_ASSETS)/%)
	for f in $(COPIED_ASSETS); do \
		cp $(SRC_ASSETS)/$$f $(BUILD_ASSETS)/$$f ; \
	done

.PHONY: assets
assets: copied_assets $(BUILD_DIR)/resume.pdf

##########
## HTML ##
##########

.PHONY: html
html: $(IN_HTML_FILES) $(SRC_ASSETS)/dl_ascii.txt src/templates.py src/build_html.py build
	python3 src/templates.py

#########
## CSS ##
#########

$(BUILD_CSS)/%.css: $(SRC_CSS)/%.css build html js
	npx tailwindcss -i $< -o $@ -c src/tailwind.config.js

.PHONY: css
css: $(OUT_CSS_FILES)

########
## JS ##
########

$(BUILD_JS)/%.js: $(SRC_JS)/%.js build
	cp $< $@

.PHONY: js
js: $(OUT_JS_FILES)

##########
## WASM ##
##########

TERMINAL_MODE_SRCS = $(wildcard $(SRC_CPP)/*.cpp)
EMCC_FLAGS = -Wall -Werror -sEXPORTED_RUNTIME_METHODS=ccall -I $(SRC_DATA)
EMCC_EXPORTS = -sEXPORTED_FUNCTIONS=_main,_key_pressed,_free

$(BUILD_JS)/terminal_mode.js: $(SRC_CPP)/terminal_mode.js $(TERMINAL_MODE_SRCS)
	emcc $(EMCC_EXPORTS) $(EMCC_FLAGS) --js-library $(SRC_CPP)/terminal_mode.js $(TERMINAL_MODE_SRCS) -o $@

.PHONY: wasm
wasm: $(BUILD_JS)/terminal_mode.js

.PHONY: clean
clean:
	rm -rf build
	rm $(SRC_ASSETS)/dl_ascii.txt

.PHONY: server
server:
	cd build && \
	python3 -m http.server $(SERVERPORT)
