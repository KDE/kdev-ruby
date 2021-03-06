/* C code produced by gperf version 3.0.4 */
/* Command-line: gperf -C -p -j1 -i 1 -g -o -t -N rb_reserved_word -k'1,3,$' gperf.txt  */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 1 "gperf.txt"

struct kwtable {const char *name; int id[2]; enum lex_state_e state;};
const struct kwtable *rb_reserved_word(const char *, unsigned int);
static const struct kwtable *reserved_word(const char *, unsigned int);
#define rb_reserved_word(str, len) reserved_word(str, len)
#line 8 "gperf.txt"
struct kwtable;

#define TOTAL_KEYWORDS 41
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 12
#define MIN_HASH_VALUE 8
#define MAX_HASH_VALUE 50
/* maximum key range = 43, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (str, len)
     register const char *str;
     register unsigned int len;
{
  static const unsigned char asso_values[] =
    {
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 26, 51, 51, 14, 51, 16,  8,
      11, 13, 51, 51, 51, 51, 10, 51, 13, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 11, 51, 13,  1, 26,
       4,  1,  8, 28, 51, 23, 51,  1,  1, 27,
       5, 19, 21, 51,  8,  3,  3, 11, 51, 21,
      24, 16, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
      51, 51, 51, 51, 51, 51
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct kwtable *
rb_reserved_word (str, len)
     register const char *str;
     register unsigned int len;
{
  static const struct kwtable wordlist[] =
    {
      {"", {0,0}, 0}, {"", {0,0}, 0}, {"", {0,0}, 0}, {"", {0,0}, 0}, {"", {0,0}, 0}, {"", {0,0}, 0}, {"", {0,0}, 0}, {"", {0,0}, 0},
#line 18 "gperf.txt"
      {"break", {tBREAK, tBREAK}, EXPR_MID},
#line 24 "gperf.txt"
      {"else", {tELSE, tELSE}, EXPR_BEG},
#line 34 "gperf.txt"
      {"nil", {tNIL, tNIL}, EXPR_END},
#line 27 "gperf.txt"
      {"ensure", {tENSURE, tENSURE}, EXPR_BEG},
#line 26 "gperf.txt"
      {"end", {tEND, tEND}, EXPR_END},
#line 43 "gperf.txt"
      {"then", {tTHEN, tTHEN}, EXPR_BEG},
#line 35 "gperf.txt"
      {"not", {tKWNOT, tKWNOT}, EXPR_ARG},
#line 28 "gperf.txt"
      {"false", {tFALSE, tFALSE}, EXPR_END},
#line 41 "gperf.txt"
      {"self", {tSELF, tSELF}, EXPR_END},
#line 25 "gperf.txt"
      {"elsif", {tELSIF, tELSIF}, EXPR_VALUE},
#line 38 "gperf.txt"
      {"rescue", {tRESCUE, modifier_rescue}, EXPR_MID},
#line 44 "gperf.txt"
      {"true", {tTRUE, tTRUE}, EXPR_END},
#line 47 "gperf.txt"
      {"until", {tUNTIL, modifier_until}, EXPR_VALUE},
#line 46 "gperf.txt"
      {"unless", {tUNLESS, modifier_unless}, EXPR_VALUE},
#line 40 "gperf.txt"
      {"return", {tRETURN, tRETURN}, EXPR_MID},
#line 21 "gperf.txt"
      {"def", {tDEF, tDEF}, EXPR_FNAME},
#line 16 "gperf.txt"
      {"and", {tKWAND, tKWAND}, EXPR_VALUE},
#line 23 "gperf.txt"
      {"do", {tDO, tDO}, EXPR_BEG},
#line 50 "gperf.txt"
      {"yield", {tYIELD, tYIELD}, EXPR_ARG},
#line 29 "gperf.txt"
      {"for", {tFOR, tFOR}, EXPR_VALUE},
#line 45 "gperf.txt"
      {"undef", {tUNDEF, tUNDEF}, EXPR_FNAME},
#line 36 "gperf.txt"
      {"or", {tKWOR, tKWOR}, EXPR_VALUE},
#line 31 "gperf.txt"
      {"in", {tIN, tIN}, EXPR_VALUE},
#line 48 "gperf.txt"
      {"when", {tWHEN, tWHEN}, EXPR_VALUE},
#line 39 "gperf.txt"
      {"retry", {tRETRY, tRETRY}, EXPR_END},
#line 30 "gperf.txt"
      {"if", {tIF, modifier_if}, EXPR_VALUE},
#line 19 "gperf.txt"
      {"case", {tCASE, tCASE}, EXPR_VALUE},
#line 37 "gperf.txt"
      {"redo", {tREDO, tREDO}, EXPR_END},
#line 33 "gperf.txt"
      {"next", {tNEXT, tNEXT}, EXPR_MID},
#line 42 "gperf.txt"
      {"super", {tSUPER, tSUPER}, EXPR_ARG},
#line 32 "gperf.txt"
      {"module", {tMODULE, tMODULE}, EXPR_VALUE},
#line 17 "gperf.txt"
      {"begin", {tBEGIN, tBEGIN}, EXPR_BEG},
#line 11 "gperf.txt"
      {"__LINE__", {tLINE, tLINE}, EXPR_END},
#line 12 "gperf.txt"
      {"__FILE__", {tFILE, tFILE}, EXPR_END},
#line 10 "gperf.txt"
      {"__ENCODING__", {tENCODING, tENCODING}, EXPR_END},
#line 14 "gperf.txt"
      {"END", {upEND, upEND}, EXPR_END},
#line 15 "gperf.txt"
      {"alias", {tALIAS, tALIAS}, EXPR_FNAME},
#line 13 "gperf.txt"
      {"BEGIN", {upBEGIN, upBEGIN}, EXPR_END},
#line 22 "gperf.txt"
      {"defined?", {tDEFINED, tDEFINED}, EXPR_ARG},
#line 20 "gperf.txt"
      {"class", {tCLASS, tCLASS}, EXPR_CLASS},
      {"", {0,0}, 0}, {"", {0,0}, 0},
#line 49 "gperf.txt"
      {"while", {tWHILE, modifier_while}, EXPR_VALUE}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}
#line 51 "gperf.txt"

