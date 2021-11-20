import re

def read_card_rows():
    with open('data/mid/cards.html') as f:
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


def strip_html_tags(str):
    return re.sub('<[^>]*>', '', str)

assert strip_html_tags('<td class="name"><a href="https://www.magicarenacardlist.com/#">Blessed Defiance</a>') == 'Blessed Defiance'


class Card:
    def __init__(self):
        self.mana = ''
        self.name = ''
        self.type = ''

    def __str__(self):
        return f'Card: {self.mana} "{self.name}" {self.type}'


def parse_mana(field):
    mana = re.findall('symbolS-([A-Z0-9])', field)
    return ''.join(mana)


def parse_card(row):
    result = Card()
    for field in row.split('</td>'):
        if field.find('class="name"') >= 0:
            result.name = strip_html_tags(field)
        elif field.find('class="type"') >= 0:
            result.type = strip_html_tags(field)
        elif field.find('class="mana"') >= 0:
            result.mana = parse_mana(field)
        else:
            # print(field)
            pass
    return result

def main():
    rows = read_card_rows()
    cards = map(parse_card, rows)
    for c in cards:
        print(c)

main()
