#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "storage_mgr.h"
#include "dberror.h"
#include "test_helper.h"

// test name
char *testName;

/* test output files */
#define TESTPF "test_pagefile.bin"

/* prototypes for test functions */
static void testCreateOpenClose(void);
static void testSinglePageContent(void);
static void testAll(void);

/* main function running all tests */
int
main (void)
{
  testName = "";
  
  initStorageManager();

  testCreateOpenClose();
  testSinglePageContent();

  testAll();  //EXTRA TESTING

  return 0;
}


/* check a return code. If it is not RC_OK then output a message, error description, and exit */
/* Try to create, open, and close a page file */
void
testCreateOpenClose(void)
{
  SM_FileHandle fh;

  testName = "test create open and close methods";

  TEST_CHECK(createPageFile (TESTPF));
  
  TEST_CHECK(openPageFile (TESTPF, &fh));
  ASSERT_TRUE(strcmp(fh.fileName, TESTPF) == 0, "filename correct");
  ASSERT_TRUE((fh.totalNumPages == 1), "expect 1 page in new file");
  ASSERT_TRUE((fh.curPagePos == 0), "freshly opened file's page position should be 0");

  TEST_CHECK(closePageFile (&fh));
  TEST_CHECK(destroyPageFile (TESTPF));

  // after destruction trying to open the file should cause an error
  ASSERT_TRUE((openPageFile(TESTPF, &fh) != RC_OK), "opening non-existing file should return an error.");

  TEST_DONE();
}

/* Try to create, open, and close a page file */
void
testSinglePageContent(void)
{
  SM_FileHandle fh;
  SM_PageHandle ph;
  int i;

  testName = "test single page content";

  ph = (SM_PageHandle) malloc(PAGE_SIZE);

  // create a new page file
  TEST_CHECK(createPageFile (TESTPF));
  TEST_CHECK(openPageFile (TESTPF, &fh));
  printf("created and opened file\n");
  // read first page into handle
  TEST_CHECK(readFirstBlock (&fh, ph));
  // the page should be empty (zero bytes)
  for (i=0; i < PAGE_SIZE; i++)
    ASSERT_TRUE((ph[i] == 0), "expected zero byte in first page of freshly initialized page");
  printf("first block was empty\n");
  // change ph to be a string and write that one to disk
  for (i=0; i < PAGE_SIZE; i++)
    ph[i] = (i % 10) + '0';
  TEST_CHECK(writeBlock (0, &fh, ph)); 
  printf("writing first block\n");

  for (i=0; i < PAGE_SIZE; i++){ ph[i] = 'a'; } //reset char array to invalid values 

  // read back the page containing the string and check that it is correct
  TEST_CHECK(readFirstBlock (&fh, ph));
  for (i=0; i < PAGE_SIZE; i++)
    ASSERT_TRUE((ph[i] == (i % 10) + '0'), "character in page read from disk is the one we expected.");
  printf("reading first block\n");

  // destroy new page file
  TEST_CHECK(destroyPageFile(TESTPF));  
  
  TEST_DONE();
}


void testAll(){

/*
  SM_FileHandle fh;
  SM_PageHandle ph;

  int i;
  testName = "test multi-page content";
  ph = (SM_PageHandle) malloc(PAGE_SIZE);
  //expect error if reading or writing unopened pagefile
  TEST_CHECK(writeBlock (0, &fh, ph)); 
  TEST_CHECK(readBlock (&fh, ph));

  //write three blocks and test if the values are correct
  TEST_CHECK(createPageFile (TESTPF));

  TEST_CHECK(getBlockPos (&fh, ph));        //ensure starting at zero pages
  
  TEST_CHECK(openPageFile (TESTPF, &fh));
  TEST_CHECK(writeBlock (0, &fh, ph)); 
  TEST_CHECK(readFirstBlock (&fh, ph));
  TEST_CHECK(getBlockPos (&fh, ph));        //ensure written 1 page

  TEST_CHECK(appendEmptyBlock (&fh, ph));
  TEST_CHECK(readBlock (&fh, ph));
  TEST_CHECK(getBlockPos (&fh, ph));        //ensure written 2 pages

  TEST_CHECK(writeCurrentBlock (&fh, ph));  
  TEST_CHECK(readBlock (&fh, ph));
  TEST_CHECK(getBlockPos (&fh, ph));        //ensure written 3 pages

  TEST_CHECK(ensureCapacity (&fh, ph));
*/
  TEST_DONE();
}