import pandas as pd


pd.set_option('display.max_columns', None)

nuclei_data = pd.read_csv('nuclear_data.csv', index_col='Unnamed: 0')

print(nuclei_data)

# Table for small nuclei
small_nuclei_data = nuclei_data[['A', 'Z', 'mass']]
small_nuclei_data = small_nuclei_data[small_nuclei_data['A'] <= 20]
small_nuclei_data.to_csv('small_nuclei_data.csv')

# for index, row in small_nuclei_data.iterrows():
#     A = int(row['A'])
#     Z = int(row['Z'])
#     mass = row['mass']
#     print(f'data.insert({{NucleiData{{{A}_m, {Z}_c}}, {mass}}});')
