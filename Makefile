
SRC = src
SRC_ASSETS = $(SRC)/assets
SRC_TEMPLATES = $(SRC)/templates
SRC_CSS = $(SRC)/css
SRC_JS = $(SRC)/js

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

release: build assets html css js

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
	jp2a --size=40x20 --invert $(SRC_ASSETS)/image.jpg > $@

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

$(BUILD_CSS)/%.css: $(SRC_CSS)/%.css build
	npx tailwindcss -i $< -o $@

.PHONY: css
css: $(OUT_CSS_FILES)

########
## JS ##
########

$(BUILD_JS)/%.js: $(SRC_JS)/%.js build
	cp $< $@

.PHONY: js
js: $(OUT_JS_FILES)

.PHONY: clean
clean:
	rm -rf build

.PHONY: server
server:
	cd build && \
	python3 -m http.server $(SERVERPORT)
