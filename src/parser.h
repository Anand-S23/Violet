#ifndef PARSER_H
#define PARSER_H

const char *token_string_list[] = {
    "NULL", "Header", "Paragraph", "Bold", "Italics",
    "Blockquote", "Unordered List", "Ordered List",
    "Code", "Break", "Link", "Image", "Continue"
};

const char *token_tags[] = {
    "NULL",
    "<h%d>\n",
    "<p>\n",
    "<strong>\n",
    "<em>\n",
    "<blockquote>\n",
    "<ul>\n",
    "<ol>\n",
    "<code class='prettyprint'>\n",
    "<br>\n",
    "<a href='%s'>\n",
    "<img src='%s'>\n",
    "",
    "MAX"
};

const char *token_end_tags[] = {
    "NULL",
    "</h%d>\n",
    "</p>\n",
    "</strong>\n",
    "</em>\n",
    "</blockquote>\n",
    "</ul>\n",
    "</ol>\n",
    "</code>\n",
    "</br>\n",
    "</a>\n",
    "</img>\n",
    "",
    "MAX"
};

typedef enum token_type_t
{
    TT_NULL,
    TT_header,
    TT_paragraph,
    TT_bold,
    TT_italics,
    TT_blockquote,
    TT_unordered_list,
    TT_ordered_list,
    TT_code,
    TT_break,
    TT_link,
    TT_image,
    TT_continue,
    TT_MAX
} token_type_t;

typedef enum external_token_type_t
{
    Image,
    Link
} external_token_type_t;

typedef struct external_token_t
{
    uint32_t primary_count;
    uint32_t secondary_count;
    const char *primary;
    const char *secondary;
} external_token_t;

typedef struct token_t
{
    token_type_t type;
    uint32_t len;
    uint32_t count;
    bool is_end_node;
    external_token_t external;
    const char *start;
} token_t;

typedef struct parser_t
{
    token_t *token_buffer;
    token_t *end_token_buffer;
    token_t current_token;
    bool should_push;
} parser_t;

static bool violet_is_char_whitespace(char c);
static bool violet_is_char_endspace(char c);
static bool violet_is_char_symbol(char c);
static bool violet_check_string_match(char *s1, char *s2, int match_num);
static bool violet_check_for_symbol_string(char *current_stream, char *symbol_stream);
static void violet_shift_last_etb_element(parser_t *parser, token_type_t last_etb_element_type);
static void violet_finish_line(parser_t *parser);
static bool violet_check_if_valid_external_token(char *stream, external_token_type_t ett);
static void violet_parse_stream(parser_t *parser, char *stream);

#endif // PARSER_H
