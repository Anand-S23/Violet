#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "../src/util.h"
#include "../src/parser.c"

// Function declerations
bool test_h1(void);
bool test_h2(void);
bool test_h3(void);
bool test_paragraph(void);
bool test_bold(void);
bool test_italics(void);

const char *test_func_names[] = {
    "test_h1",
    "test_h2",
    "test_h3",
    "test_paragraph",
    "test_bold",
    "test_italics"
};

bool (*test_funcs[])(void) = {
    test_h1,
    test_h2,
    test_h3,
    test_paragraph,
    test_bold,
    test_italics
};

// Util

bool test_verify_matching_array(token_t *tb_a, int tb_a_size,
                                token_t *tb_b, int tb_b_size)
{
    if (tb_a_size != tb_b_size)
    {
        printf(" - Token buffer sizes do not match\n");
        return false;
    }

    for (int i = 0; i < tb_a_size; ++i)
    {
        // TODO: Check external_token

        if (tb_a[i].type != tb_b[i].type)
        {
            printf("\n - Token types do not match at index %d\n", i);
            return false;
        }
        else if (tb_a[i].len != tb_b[i].len)
        {
            printf("\n - Token content len do not match at index %d\n", i);
            return false;
        }
        else if (tb_a[i].count != tb_b[i].count)
        {
            printf("\n - Token count do not match at index %d\n", i);
            return false;
        }
        else if (tb_a[i].is_end_node != tb_b[i].is_end_node)
        {
            printf("\n - Token mismatch end type at index %d\n", i);
            return false;
        }
        else if (tb_a[i].start != tb_b[i].start)
        {
            printf("\n - Token content start do not match at index %d\n", i);
            return false;
        }
    }

    return true;
}

char *test_get_input(const char *value, int value_size)
{
    int byte_size = sizeof(char) * (value_size + 1);
    char *test_input = (char *)malloc(byte_size);
    strncpy(test_input, value, value_size);
    test_input[value_size + 1] = '\0';
    return test_input;
}

// Tests //

bool test_h1(void)
{
    const char *input_val = "# Header 1\n";
    int input_val_size = strlen(input_val);
    int start_offset = 2;
    int removeable_characters = 3;
    
    char *test_input = test_get_input(input_val, input_val_size);

    // Generate the buffer from the test input
    parser_t gen = (parser_t){0}; 
    violet_parse_stream(&gen, test_input);

    // Generate what the output buffer should be
    token_t test_tb[2] = {
        (token_t) {
            .type = TT_header,
            .count = 1,
            .len = (input_val_size - removeable_characters),
            .start = (test_input + start_offset),
            .external = (external_token_t){0},
            .is_end_node = 0
        },
        (token_t) {
            .type = TT_header,
            .count = 1,
            .len = 0,
            .start = NULL,
            .external = (external_token_t){0},
            .is_end_node = 1
        }
    }; 

    // Compare the buffers to make sure they are the same
    bool result = test_verify_matching_array(gen.token_buffer,
                                             sb_len(gen.token_buffer),
                                             test_tb, arr_size(test_tb));
    free(test_input);
    return result;
}

bool test_h2(void)
{
    const char *input_val = "## Header 2\n";
    int input_val_size = strlen(input_val);
    int start_offset = 3;
    int removeable_characters = 4;
    
    char *test_input = test_get_input(input_val, input_val_size);

    // Generate the buffer from the test input
    parser_t gen = (parser_t){0}; 
    violet_parse_stream(&gen, test_input);

    // Generate what the output buffer should be
    token_t test_tb[2] = {
        (token_t) {
            .type = TT_header,
            .count = 2,
            .len = (input_val_size - removeable_characters),
            .start = (test_input + start_offset),
            .external = (external_token_t){0},
            .is_end_node = 0
        },
        (token_t) {
            .type = TT_header,
            .count = 2,
            .len = 0,
            .start = NULL,
            .external = (external_token_t){0},
            .is_end_node = 1
        }
    }; 

    // Compare the buffers to make sure they are the same
    bool result = test_verify_matching_array(gen.token_buffer,
                                             sb_len(gen.token_buffer),
                                             test_tb, arr_size(test_tb));
    free(test_input);
    return result;
}

bool test_h3(void)
{
    const char *input_val = "### Header 3\n";
    int input_val_size = strlen(input_val);
    int start_offset = 4;
    int removeable_characters = 5;
    
    char *test_input = test_get_input(input_val, input_val_size);

    // Generate the buffer from the test input
    parser_t gen = (parser_t){0}; 
    violet_parse_stream(&gen, test_input);

    // Generate what the output buffer should be
    token_t test_tb[2] = {
        (token_t) {
            .type = TT_header,
            .count = 3,
            .len = (input_val_size - removeable_characters),
            .start = (test_input + start_offset),
            .external = (external_token_t){0},
            .is_end_node = 0
        },
        (token_t) {
            .type = TT_header,
            .count = 3,
            .len = 0,
            .start = NULL,
            .external = (external_token_t){0},
            .is_end_node = 1
        }
    }; 

    // Compare the buffers to make sure they are the same
    bool result = test_verify_matching_array(gen.token_buffer,
                                             sb_len(gen.token_buffer),
                                             test_tb, arr_size(test_tb));
    free(test_input);
    return result;
}

bool test_paragraph(void)
{
    const char *input_val = "This is a paragraph\n";
    int input_val_size = strlen(input_val);
    int start_offset = 0;
    int removeable_characters = 1;
    
    char *test_input = test_get_input(input_val, input_val_size);

    // Generate the buffer from the test input
    parser_t gen = (parser_t){0}; 
    violet_parse_stream(&gen, test_input);

    // Generate what the output buffer should be
    token_t test_tb[2] = {
        (token_t) {
            .type = TT_paragraph,
            .count = 0,
            .len = (input_val_size - removeable_characters),
            .start = (test_input + start_offset),
            .external = (external_token_t){0},
            .is_end_node = 0
        },
        (token_t) {
            .type = TT_paragraph,
            .count = 0,
            .len = 0,
            .start = NULL,
            .external = (external_token_t){0},
            .is_end_node = 1
        }
    }; 

    // Compare the buffers to make sure they are the same
    bool result = test_verify_matching_array(gen.token_buffer,
                                             sb_len(gen.token_buffer),
                                             test_tb, arr_size(test_tb));
    free(test_input);
    return result;
}

bool test_bold(void)
{
    const char *input_val = "**Test Bold**\n";
    int input_val_size = strlen(input_val);
    int start_offset = 2;
    int removeable_characters = 5;
    
    char *test_input = test_get_input(input_val, input_val_size);

    // Generate the buffer from the test input
    parser_t gen = (parser_t){0}; 
    violet_parse_stream(&gen, test_input);

    // Generate what the output buffer should be
    token_t test_tb[2] = {
        (token_t) {
            .type = TT_bold,
            .count = 2,
            .len = (input_val_size - removeable_characters),
            .start = (test_input + start_offset),
            .external = (external_token_t){0},
            .is_end_node = 0
        },
        (token_t) {
            .type = TT_bold,
            .count = 0,
            .len = 0,
            .start = NULL,
            .external = (external_token_t){0},
            .is_end_node = 1
        }
    }; 

    // Compare the buffers to make sure they are the same
    bool result = test_verify_matching_array(gen.token_buffer,
                                             sb_len(gen.token_buffer),
                                             test_tb, arr_size(test_tb));
    free(test_input);
    return result;
}

bool test_italics(void)
{
    const char *input_val = "*Test Italics*\n";
    int input_val_size = strlen(input_val);
    int start_offset = 1;
    int removeable_characters = 3;
    
    char *test_input = test_get_input(input_val, input_val_size);

    // Generate the buffer from the test input
    parser_t gen = (parser_t){0}; 
    violet_parse_stream(&gen, test_input);

    // Generate what the output buffer should be
    token_t test_tb[2] = {
        (token_t) {
            .type = TT_italics,
            .count = 1,
            .len = (input_val_size - removeable_characters),
            .start = (test_input + start_offset),
            .external = (external_token_t){0},
            .is_end_node = 0
        },
        (token_t) {
            .type = TT_italics,
            .count = 0,
            .len = 0,
            .start = NULL,
            .external = (external_token_t){0},
            .is_end_node = 1
        }
    }; 

    // Compare the buffers to make sure they are the same
    bool result = test_verify_matching_array(gen.token_buffer,
                                             sb_len(gen.token_buffer),
                                             test_tb, arr_size(test_tb));
    free(test_input);
    return result;
}

// Core // 

int main(void)
{
    uint32_t test_funcs_size = arr_size(test_funcs);
    // Name array has to be same length as the test funcs
    assert(test_funcs_size == arr_size(test_func_names));

    bool (*current)(void);
    uint32_t tests_passed_count = 0;
    for (uint32_t i = 0; i < test_funcs_size; ++i)
    {
        current = test_funcs[i];

        printf("%s: ", test_func_names[i]);
        if (current())
        {
            // Test passed
            tests_passed_count++;
            printf("PASSED\n");
        }
        else
        {
            // Test failed
            printf("FAILED\n");
        }
    }

    printf("\nTest finished running...\n - (%d/%d) passed\n", 
        tests_passed_count, test_funcs_size);

    return 0;
}
