#include <stdio.h>
#include <stdlib.h>
#include "crawler.h"
#include "curl.h"

// Function to parse command-line arguments.
// It extracts seedURL, pageDirectory, and maxDepth from the command line.
static void parseArgs(const int argc, char *argv[], char **seedURL, char **pageDirectory, int *maxDepth) {
    // Ensure the correct number of arguments are provided.
    if (argc != 4) {
        fprintf(stderr, "Usage: %s seedURL pageDirectory maxDepth\n", argv[0]);
        exit(1);
    }

    // Assign values to the respective variables.
    *seedURL = argv[1];
    *pageDirectory = argv[2];
    *maxDepth = atoi(argv[3]);  // Convert string to integer.

    // Validate maxDepth is within the allowed range.
    if (*maxDepth < 0 || *maxDepth > 10) {
        fprintf(stderr, "maxDepth must be between 0 and 10\n");
        exit(1);
    }
}

// Function to crawl webpages starting from the seedURL.
// It uses a bag to store pages to crawl and a hashtable to track seen URLs.
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
    // Initialize data structures for crawling.
    bag_t *pagesToCrawl = bag_init();
    hashtable_t *pagesSeen = hashtable_init();

    // Add the seed page to the bag and hashtable.
    webpage_t *seedPage = webpage_new(seedURL, 0, NULL);
    bag_insert(pagesToCrawl, seedPage);
    hashtable_insert(pagesSeen, seedURL, NULL);

    // Main crawling loop.
    while ((seedPage = bag_extract(pagesToCrawl)) != NULL) {
        // Fetch the page content.
        if (pagefetcher(seedPage)) {
            // Save the fetched page to the directory.
            pagedir_save(seedPage, pageDirectory, seedPage->depth);

            // Scan for new URLs if depth limit not reached.
            if (seedPage->depth < maxDepth) {
                pageScan(seedPage, pagesToCrawl, pagesSeen);
            }
        }
        // Clean up the current webpage.
        webpage_delete(seedPage);
    }

    // Clean up resources.
    bag_delete(pagesToCrawl, NULL);
    hashtable_delete(pagesSeen, NULL);
}

// Function to scan a webpage for URLs and process them.
static void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen) {
    int pos = 0;
    char *result;

    // Iterate over all URLs found on the page.
    while ((result = webpage_getNextURL(page, &pos)) != NULL) {
        // Normalize the URL.
        char *normalizedURL = normalizeURL(webpage_getURL(page), result);
        free(result);  // Free the URL retrieved by webpage_getNextURL.

        // Check if the URL is internal and not already seen.
        if (normalizedURL != NULL && isInternalURL(webpage_getURL(page), normalizedURL)) {
            // Add new internal URL to the bag if not seen.
            if (hashtable_insert(pagesSeen, normalizedURL, "")) {
                webpage_t *newPage = webpage_new(normalizedURL, webpage_getDepth(page) + 1, NULL);
                bag_insert(pagesToCrawl, newPage);
            } else {
                free(normalizedURL);  // Free the normalized URL if already seen.
            }
        } else {
            free(normalizedURL);  // Free the URL if it's external.
        }
    }
}

// Main function: Entry point of the crawler.
int main(const int argc, char *argv[]) {
    // Variables for storing parsed arguments.
    char *seedURL, *pageDirectory;
    int maxDepth;

    // Parse the command line arguments.
    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);

    // Start the crawling process.
    crawl(seedURL, pageDirectory, maxDepth);

    return 0;  // Successful execution.
}
