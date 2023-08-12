# Violet

<p align='center'><img alt='Violet Logo' src='logo.webp' width=30%></p>

Violet is a simple static website generator written in C. Violet allows users
to write pages in mark down and will use a configuration file to build a website
how users would like. Though there will be an example site where
css will be included, you will need to write own css for the customization of the
website.

## Quick Start

After cloning the violet directory, the follow commands can be run depending on
your OS to get a quick start with violet. GCC complier must be installed on the
system for the build scripts to work.

NOTE: example_config.cfg has layout for config files

**Linux:**
```
$ chmod +x ./build.sh
$ ./build.sh
$ ./bin/violet ./example_config.cfg
```

**Windows and MacOS:**
Currently Windows and MacOS are not directly supported, will be added later on

## Supported Markdown

**Heading**
```
# H1
## H2
### H3
```

**Bold**
```
**Bold Text**
```

**Italic**
```
*Italicized Text*
```

**Blockquote**
```
> Blockquote
```

**Code**
```
`Code`
```

**Break**
```
---
```

**Link**
```
[Title](https://www.website.com)
```

**Image**
```
![Alt Text](image.jpg)
```

### In Development

**Ordered List**
```
1. First Item
2. Second Item
3. Third Item
```

**Unordered List**
```
- First Item
- Second Item
- Third Item
```

## To Contribute

There are no major rules in terms of pull requests at the moments for requriements,
other than the changes must be on a seperate branch, where the name of the branch
clear outlines the feature that is being changed. I would also advise using the
same general code format that is currently being used.

## Contributions

Special thanks to the following contributors:
- alexz89142

