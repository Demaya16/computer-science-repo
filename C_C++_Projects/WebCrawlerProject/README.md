# Assignment Web Crawler README

## Description

The Web Crawler is a C application designed to crawl web pages starting from a seed URL. It fetches pages up to a specified depth, processing internal links and saving each page to a designated directory. This project was implemented with a focus on efficient URL management and memory handling.

## Author

- Devin Maya
- Email: demaya@ucsc.edu
- Assignment Web Crawler

## File Names and What They Do

- `crawler.c`: The main source file containing the logic for the web crawler.
- `crawler.h`: Header file with the definitions for the structures and functions used by the crawler.
- `pagedir.c`: Module for saving downloaded pages.
- `pagedir.h`: Header file for the `pagedir` module.
- `hashtable.c`: Implementation of a hashtable used for tracking seen URLs.
- `hashtable.h`: Header file for the hashtable module.
- `bag.c`: Implementation of a bag data structure for managing web pages to be crawled.
- `bag.h`: Header file for the bag module.
- `url.c`: Module for URL normalization and validation.
- `url.h`: Header file for the URL module.
- `curl.c`: Wrapper around libcurl for fetching web pages.
- `curl.h`: Header file for the curl wrapper.
- `.gitignore`: Specifies files to be ignored by Git.
- `Makefile`: Manages the compilation process.
- `README.md`: This file, providing documentation for the project.

## Compilation Process and How to Run

To compile the Web Crawler, use the following commands:

```bash
make        # Compiles the Web Crawler.


