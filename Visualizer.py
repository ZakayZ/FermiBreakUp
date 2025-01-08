import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import json


def draw_particle_count():
    C12 = pd.read_csv('Results/C12.csv')
    C13 = pd.read_csv('Results/C13.csv')
    N12 = pd.read_csv('Results/N12.csv')
    N13 = pd.read_csv('Results/N13.csv')

    def load_correct_data(filename: str):
        df = pd.DataFrame()
        energy = []
        avg = []
        with open(filename, 'r') as f:
            lines = f.readlines()
            for line in lines:
                data = line.split()
                energy.append(float(data[0]))
                avg.append(float(data[1]))

        df['energy'] = np.array(energy)
        df['avg_count'] = np.array(avg)

        return df

    C12_corr = load_correct_data('Results/tabl_C12.dat')
    C13_corr = load_correct_data('Results/tabl_C13.dat')
    N12_corr = load_correct_data('Results/tabl_N12.dat')
    N13_corr = load_correct_data('Results/tabl_N13.dat')

    plt.subplots(2, 2, sharex='col', sharey='row', figsize=(14, 10))

    names = [r'$^{12}_6C$', r'$^{13}_6C$', r'$^{12}_7N$', r'$^{13}_7N$']
    data = [C12, C13, N12, N13]
    data_corr = [C12_corr, C13_corr, N12_corr, N13_corr]
    for idx in range(len(data)):
        plt.subplot(2, 2, idx + 1)
        plt.scatter(data[idx]['energy'], data[idx]['avg_count'], s=5, label='Our implementation')
        plt.errorbar(data[idx]['energy'], data[idx]['avg_count'],
                     xerr=None, yerr=data[idx]['avg_count'] / np.sqrt(1e4))

        plt.scatter(data_corr[idx]['energy'], data_corr[idx]['avg_count'], s=20, label='Fermi break-up (F77)')

        plt.minorticks_on()
        plt.grid(True)
        plt.grid(True, which='minor', linestyle='--', alpha=0.4)
        plt.xlabel('Excitation energy MeV/nucleon')
        plt.ylabel('Average fragment multiplicity')
        plt.title('Fermi break-up of ' + names[idx])
        plt.legend()

    # plt.suptitle("Average fragment count with Fermi Break Up")
    plt.tight_layout()
    plt.savefig("data/img/FragmentCount.png", bbox_inches='tight')
    plt.show()


# draw_particle_count()


def parse_momentum(filename: str):
    data = {
        'x': [],
        'y': [],
        'z': [],
        'e': [],
    }
    with open(filename, 'r') as stat_component:
        lines = stat_component.readlines()
        for line in lines:
            momenta = line.split()
            for momentum in momenta:
                x, y, z = momentum.split(',')
                z, e = z.split(';')
                data['x'].append(float(x[1:]))
                data['y'].append(float(y))
                data['z'].append(float(z))
                data['e'].append(float(e[:-1]))

    data['x'] = np.array(data['x']) / 1e3
    data['y'] = np.array(data['y']) / 1e3
    data['z'] = np.array(data['z']) / 1e3
    data['e'] = np.array(data['e']) / 1e3

    return pd.DataFrame(data)


def draw_momentum():
    stat_data = parse_momentum('Results/stat.data')
    x_data = parse_momentum('Results/mov_x.data')
    y_data = parse_momentum('Results/mov_y.data')
    z_data = parse_momentum('Results/mov_z.data')

    rows = 4
    columns = 3
    plt.subplots(rows, columns, figsize=(18, 10))
    data = [stat_data, x_data, y_data, z_data]
    names = ['stationary', 'x', 'y', 'z']
    for i in range(rows):
        local_data = data[i]
        plt.subplot(rows, columns, columns * i + 1)
        plt.grid(True)
        plt.scatter(local_data['z'][1:], np.sqrt(local_data['x'] ** 2 + local_data['y'] ** 2)[1:],
                    s=5, label='fragments', alpha=0.2)
        plt.scatter(local_data['z'][0], np.sqrt(local_data['x'] ** 2 + local_data['y'] ** 2)[0], label='initial fragment ',
                    color='red')
        plt.xlabel('z, GeV/nucleon')
        plt.ylabel(r'$\sqrt{x^2 + y^2}$, GeV/nucleon')
        plt.title('z vs xOy')
        plt.legend()

        plt.subplot(rows, columns, columns * i + 2)
        plt.grid(True)
        plt.scatter(local_data['x'][1:], np.sqrt(local_data['z'] ** 2 + local_data['y'] ** 2)[1:],
                    s=5, label='fragments', alpha=0.2)
        plt.scatter(local_data['x'][0], np.sqrt(local_data['z'] ** 2 + local_data['y'] ** 2)[0], label='initial',
                    color='red')
        plt.xlabel('x, GeV/nucleon')
        plt.ylabel(r'$\sqrt{y^2 + z^2}$, GeV/nucleon')
        plt.title('x vs yOz')
        plt.legend()

        plt.subplot(rows, columns, columns * i + 3)
        plt.grid(True)
        plt.scatter(local_data['y'][1:], np.sqrt(local_data['x'] ** 2 + local_data['z'] ** 2)[1:],
                    s=5, label='fragments', alpha=0.2)
        plt.scatter(local_data['y'][0], np.sqrt(local_data['x'] ** 2 + local_data['z'] ** 2)[0], label='initial',
                    color='red')
        plt.xlabel('y, GeV/nucleon')
        plt.ylabel(r'$\sqrt{x^2 + z^2}$, GeV/nucleon')
        plt.title('y vs zOx')
        plt.legend()

    plt.suptitle(r"Fermi break-up of $^{12}_6$N with excitation energy 5 MeV/nucleon")
    plt.tight_layout()
    plt.savefig('data/img/FragmentDistribution2D.png', bbox_inches='tight')
    plt.show()


draw_momentum()


def draw_momentum_distr():
    stat_data = parse_momentum('Results/stat.data')
    x_data = parse_momentum('Results/mov_x.data')
    y_data = parse_momentum('Results/mov_y.data')
    z_data = parse_momentum('Results/mov_z.data')

    rows = 3
    columns = 4
    plt.subplots(rows, columns, figsize=(18, 10), sharey="row")
    data = [x_data, y_data, z_data, stat_data]
    names = ['x = 10 GeV/nucleon', 'y = 10 GeV/nucleon', 'z = 10 GeV/nucleon', 'e = 10 GeV/nucleon', ]
    bins = 50
    for i in range(rows):
        local_data = data[i]
        weights = 100 * np.ones_like(local_data['x'][1:])/float(len(local_data['x'][1:]))

        plt.subplot(rows, 4, columns * i + 1)
        plt.grid(True)
        plt.hist(local_data['x'][1:], bins=bins, weights=weights)
        plt.xlabel('x component, GeV/nucleon')
        plt.ylabel('probability, %')
        plt.axvline(x=(10 if i == 0 else 0), color='red', label="initial")
        plt.title(f'x-distribution with {names[i]}')
        plt.legend()

        plt.subplot(rows, columns, columns * i + 2)
        plt.grid(True)
        plt.hist(local_data['y'][1:], bins=bins, weights=weights)
        plt.axvline(x=(10 if i == 1 else 0), color='red', label="initial")
        plt.xlabel('y component, GeV/nucleon')
        plt.ylabel('probability, %')
        plt.title(f'y-distribution with {names[i]}')
        plt.legend()

        plt.subplot(rows, columns, columns * i + 3)
        plt.grid(True)
        plt.hist(local_data['z'][1:], bins=bins, weights=weights)
        plt.axvline(x=(10 if i == 2 else 0), color='red', label="initial")
        plt.xlabel('z component, GeV/nucleon')
        plt.ylabel('probability, %')
        plt.title(f'z-distribution with {names[i]}')
        plt.legend()

        plt.subplot(rows, columns, columns * i + 4)
        plt.grid(True)
        plt.hist(local_data['e'][1:], bins=bins, weights=weights)
        plt.axvline(x=10, color='red', label="initial")
        plt.xlabel('e component, GeV/nucleon')
        plt.ylabel('probability, %')
        plt.title(f'e-distribution with {names[i]}')
        plt.legend()

    plt.suptitle(r"Fermi break-up of $^{12}_6$N with excitation energy 5 MeV/nucleon")
    plt.tight_layout()
    plt.savefig('data/img/FragmentDistribution.png', bbox_inches='tight')
    plt.show()


# draw_momentum_distr()


def get_az_df(data):
    A = []
    Z = []
    for exp in data:
        for el in exp:
            if el['A'] != 0:
                A.append(el['A'])
                Z.append(el['Z'])
    return pd.DataFrame({"A": A, "Z": Z})


def draw_distribution():
    elements = ["C12_05", "C12_4", "C13_05", "C13_4", "N12_05", "N12_4", "N13_05", "N13_4", "Au197_05", "Au197_4"]
    names = [r"$^{12}_6C$", r"$^{13}_6C$", r"$^{12}_7N$", r"$^{13}_7N$", r"$^{197}_{79}Au$"]
    plt.subplots(2, 5, figsize=(18, 10))
    for id, element in enumerate(elements):
        with open(f"Results/{element}_distr.dat", "r") as f:
            res = get_az_df(json.load(f))
            plt.subplot(5, 2, id + 1)
            plt.scatter(x=res["A"], y=res["Z"], alpha=0.2)
            plt.grid(True)
            plt.grid(True, which='minor')
            plt.minorticks_on()
            plt.xlabel('A')
            plt.ylabel('Z')
            plt.title(f'{names[id // 2]} {"0.5" if id % 2 == 0 else "4.0"} MeV/nucleon')

    plt.tight_layout()
    plt.suptitle("fragments distribution")
    plt.savefig(f"data/img/HandlerCountScatter.png", bbox_inches='tight')

    plt.show()


# draw_distribution()
