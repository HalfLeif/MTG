import re

def _parse_order(str):
    match = re.search('<br>([0-9]+). ([^<>]*)', str)
    if match:
        return (match[2], match[1])
    return None

def _read_cards(filename):
    with open(filename) as f:
        raw = None
        for line in f:
            if line.find('class="pick_order_tier"') >= 0:
                raw = line
                break

        assert raw
        return re.split('<div class="pick_order_card_container">(.*?)</div>', raw)


def read_order(filename):
    card_divs = _read_cards(filename)
    return filter(None, map(_parse_order, card_divs))
