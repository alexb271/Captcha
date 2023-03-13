client_source = '../project_client/client.c'
util_fn_source = '../project_server/util_functions.c'

test_success = executable('test_success', 'test_success.c')
test('test_success', test_success)

test_fail = executable('test_fail', 'test_fail.c')
test('test_fail', test_fail, should_fail : true)

captcha_add_correct = executable('captcha_add_correct', 'captcha_add_correct.c', client_source)
test('captcha_add_correct', captcha_add_correct, is_parallel : false)

captcha_add_wrong = executable('captcha_add_wrong', 'captcha_add_wrong.c', client_source)
test('captcha_add_wrong', captcha_add_wrong, is_parallel : false)

captcha_select_correct = executable('captcha_select_correct', 'captcha_select_correct.c', client_source)
test('captcha_select_correct', captcha_select_correct, is_parallel : false)

captcha_select_wrong = executable('captcha_select_wrong', 'captcha_select_wrong.c', client_source)
test('captcha_select_wrong', captcha_select_wrong, is_parallel : false)

num_format_correct = executable('num_format_correct', 'num_format_correct.c', util_fn_source)
test('num_format_correct', num_format_correct)

num_format_wrong = executable('num_format_wrong', 'num_format_wrong.c', util_fn_source)
test('num_format_wrong', num_format_wrong)
