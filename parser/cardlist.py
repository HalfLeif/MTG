import re

def _read_card_rows(filename):
    with open(filename) as f:
        table_raw = []
        start = False
        for line in f:
            if line.find('<tbody id="cardTableBody">') >= 0:
                start = True
            if start:
                table_raw.append(line)
            if line.find('</tbody>') >= 0:
                break
        table_str = ' '.join(table_raw)
        return table_str.split('</tr>')


def _strip_html_tags(str):
    return re.sub('<[^>]*>', '', str)

assert _strip_html_tags('<td class="name"><a href="https://www.magicarenacardlist.com/#">Blessed Defiance</a>') == 'Blessed Defiance'


class Card:
    def __init__(self):
        self.mana = ''
        self.name = ''
        self.type = ''
        self.order = None

    def __str__(self):
        return f'Card: {self.order}. {self.mana} "{self.name}" {self.type}'

    def header():
        return ('mana', 'name', 'type', 'order')

    def fields(self):
        return (self.mana, self.name, self.type, self.order)


def _parse_mana(field):
    mana = re.findall('symbolS-([A-Z0-9])', field)
    return ''.join(mana)

assert _parse_mana('<td class="mana"><i class="symbolS symbolS-1"></i><i class="symbolS symbolS-G"></i></td>') == '1G'

def _parse_card(row):
    result = Card()
    for field in row.split('</td>'):
        if field.find('class="name"') >= 0:
            result.name = _strip_html_tags(field)
        elif field.find('class="type"') >= 0:
            result.type = _strip_html_tags(field)
        elif field.find('class="mana"') >= 0:
            result.mana = _parse_mana(field)
        else:
            # print(field)
            pass
    # print(f'Parsed card {result.name}')
    return result

def read_cards(filename):
    rows = _read_card_rows(filename)
    cards = map(_parse_card, rows)
    return filter(lambda x: x.name, cards)
